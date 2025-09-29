import torch
import torch.nn as nn
import torch.optim as optim
import torch.nn.functional as F
from torch.utils.data import DataLoader, Dataset
import torchvision.transforms.v2 as transforms_v2
from torchvision.tv_tensors import BoundingBoxes
from torchvision.datasets import VOCDetection
from torchvision.models import efficientnet_b3, EfficientNet_B3_Weights
import os, shutil
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as patches
from PIL import Image
import xml.etree.ElementTree as ET
import kagglehub
import time
import torch
import torch.nn.functional as F
import math

# Force NVIDIA GPU usage
os.environ['CUDA_DEVICE_ORDER'] = 'PCI_BUS_ID'
os.environ['CUDA_VISIBLE_DEVICES'] = '0'
os.environ['HIP_VISIBLE_DEVICES'] = ''

plt.switch_backend('TkAgg')
plt.ion()

device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')

# ==================== SQUARE CROP TRANSFORM ====================
class SquareCropTransform:
    """Square crop based on shorter side to avoid distortion"""
    def __init__(self, random_crop=True):
        self.random_crop = random_crop
    
    def __call__(self, sample):
        # Handle both single image and sample dictionary
        if isinstance(sample, dict):
            img = sample["image"]
            has_boxes = "boxes" in sample
        else:
            img = sample
            has_boxes = False
        
        width, height = img.size
        min_dim = min(width, height)
        
        if self.random_crop:
            # Random crop for training - provides data augmentation
            if width > height:
                left = np.random.randint(0, width - min_dim + 1)
                top = 0
            else:
                left = 0
                top = np.random.randint(0, height - min_dim + 1)
        else:
            # Center crop for validation - consistent evaluation
            if width > height:
                left = (width - min_dim) // 2
                top = 0
            else:
                left = 0
                top = (height - min_dim) // 2
        
        right = left + min_dim
        bottom = top + min_dim
        
        # Crop the image
        cropped_img = img.crop((left, top, right, bottom))
        
        if isinstance(sample, dict):
            # Update the sample dictionary
            result = sample.copy()
            result["image"] = cropped_img
            
            # If there are bounding boxes, we need to adjust them
            if has_boxes:
                boxes = sample["boxes"]
                # Convert boxes to the cropped coordinate system
                boxes_data = boxes.data.clone()
                boxes_data[:, [0, 2]] -= left  # Adjust x coordinates
                boxes_data[:, [1, 3]] -= top   # Adjust y coordinates
                
                # Clamp to the new image bounds
                boxes_data[:, [0, 2]] = torch.clamp(boxes_data[:, [0, 2]], 0, min_dim)
                boxes_data[:, [1, 3]] = torch.clamp(boxes_data[:, [1, 3]], 0, min_dim)
                
                # Create new BoundingBoxes with updated canvas size
                from torchvision.tv_tensors import BoundingBoxes
                result["boxes"] = BoundingBoxes(boxes_data, format=boxes.format, canvas_size=(min_dim, min_dim))
            
            return result
        else:
            return cropped_img

# ==================== EFFICIENTNET-B3 DETECTOR ====================
class EfficientNetDetector(nn.Module):
    def __init__(self, num_classes=3, grid_size=13):
        super(EfficientNetDetector, self).__init__()
        self.grid_size = grid_size
        self.num_classes = num_classes
        
        print(f"🚀 Loading pre-trained EfficientNet-B3 backbone for {num_classes} classes...")
        
        # ✅ EFFICIENTNET-B3: Load pre-trained weights
        self.backbone = efficientnet_b3(weights=EfficientNet_B3_Weights.IMAGENET1K_V1)
        backbone_out_channels = 1536  # EfficientNet-B3 output channels
        print("✅ EfficientNet-B3: 12.0M params, optimal accuracy/efficiency balance")
        
        # Remove the classifier (only keep feature extractor)
        self.backbone = self.backbone.features
        
        # ✅ EFFICIENT FREEZING: Freeze early blocks for stability
        for i, block in enumerate(self.backbone):
            if i < 4:  # Freeze first 4 blocks
                for param in block.parameters():
                    param.requires_grad = False # 학습이 안되게
        
        print(f"✅ EfficientNet-B3 backbone loaded with ImageNet weights!")
        print(f"✅ First 4 blocks frozen, last blocks will fine-tune")
        print(f"✅ Output channels: {backbone_out_channels}")
        
        # Adaptive pooling to get consistent output size
        self.adaptive_pool = nn.AdaptiveAvgPool2d((grid_size, grid_size))
        
        # ✅ EFFICIENT FEATURE PROCESSING: Streamlined architecture
        self.feature_reducer = nn.Sequential(
            nn.Conv2d(backbone_out_channels, 512, kernel_size=1),  # 1x1 conv for efficiency
            nn.BatchNorm2d(512),
            nn.ReLU(inplace=True),
            nn.Dropout2d(0.1),
            nn.Conv2d(512, 256, kernel_size=3, padding=1),
            nn.BatchNorm2d(256),
            nn.ReLU(inplace=True)
        )
        
        # Detection heads with improved architecture
        self.objectness_head = nn.Sequential(
            nn.Conv2d(256, 128, kernel_size=3, padding=1),
            nn.BatchNorm2d(128),
            nn.ReLU(inplace=True),
            nn.Dropout2d(0.1),
            nn.Conv2d(128, 64, kernel_size=3, padding=1),
            nn.BatchNorm2d(64),
            nn.ReLU(inplace=True),
            nn.Conv2d(64, 1, kernel_size=1)
        )
        
        self.classification_head = nn.Sequential(
            nn.Conv2d(256, 128, kernel_size=3, padding=1),
            nn.BatchNorm2d(128),
            nn.ReLU(inplace=True),
            nn.Dropout2d(0.1),
            nn.Conv2d(128, 64, kernel_size=3, padding=1),
            nn.BatchNorm2d(64),
            nn.ReLU(inplace=True),
            nn.Conv2d(64, num_classes, kernel_size=1)
        )
        
        self.bbox_head = nn.Sequential(
            nn.Conv2d(256, 128, kernel_size=3, padding=1),
            nn.BatchNorm2d(128),
            nn.ReLU(inplace=True),
            nn.Dropout2d(0.1),
            nn.Conv2d(128, 64, kernel_size=3, padding=1),
            nn.BatchNorm2d(64),
            nn.ReLU(inplace=True),
            nn.Conv2d(64, 4, kernel_size=1)
        )
        
        # Initialize detection heads
        self._initialize_detection_heads()
        
    def _initialize_detection_heads(self):
        """Initialize detection heads with Xavier/He initialization"""
        modules_to_init = [self.feature_reducer, self.objectness_head, 
                          self.classification_head, self.bbox_head]
        
        for module in modules_to_init:
            for m in module.modules():
                if isinstance(m, nn.Conv2d):
                    nn.init.kaiming_normal_(m.weight, mode='fan_out', nonlinearity='relu')
                    if m.bias is not None:
                        nn.init.constant_(m.bias, 0)
                elif isinstance(m, nn.BatchNorm2d):
                    nn.init.constant_(m.weight, 1)
                    nn.init.constant_(m.bias, 0)
        
        # Special objectness initialization for faster convergence
        with torch.no_grad():
            self.objectness_head[-1].bias.fill_(-2.0)
            
        print("✅ Detection heads initialized (EfficientNet keeps ImageNet weights)")
        
    def forward(self, x):
        # Extract features using EfficientNet backbone
        features = self.backbone(x)  # [batch, channels, H, W]
        
        # Adapt to grid size
        features = self.adaptive_pool(features)  # [batch, channels, 13, 13]
        
        # Reduce feature dimensions efficiently
        features = self.feature_reducer(features)  # [batch, 256, 13, 13]
        
        # Detection predictions
        objectness = self.objectness_head(features)
        classification = self.classification_head(features)
        bbox_regression = self.bbox_head(features)
        
        # Reshape for processing
        objectness = objectness.permute(0, 2, 3, 1)
        classification = classification.permute(0, 2, 3, 1)
        bbox_regression = bbox_regression.permute(0, 2, 3, 1)
        
        return objectness, classification, bbox_regression

# ==================== PERSON/CAT/DOG DATASET ====================
class PersonCatDogVOCDataset(Dataset):
    def __init__(self, image_set='train', grid_size=13, input_size=224):
        self.grid_size = grid_size
        self.image_set = image_set
        self.input_size = input_size

        print(f"Downloading VOC dataset for Person/Cat/Dog detection {image_set}...")
        try:
            voc_path = kagglehub.dataset_download("huanghanchina/pascal-voc-2012")
            voc2012 = os.path.join(voc_path, "VOC2012")
            vocdevkit = os.path.join(voc_path, "VOCdevkit")
            fixed_voc2012 = os.path.join(vocdevkit, "VOC2012")

            if os.path.isdir(voc2012):
                os.makedirs(vocdevkit, exist_ok=True)
                if not os.path.isdir(fixed_voc2012):
                    shutil.move(voc2012, fixed_voc2012)

            self.voc = VOCDetection(root=voc_path, year='2012', image_set=image_set, download=False)
            print(f"VOC dataset loaded for Person/Cat/Dog {image_set}")

        except Exception as e:
            print(f"Dataset preparation failed: {e}")
            raise RuntimeError("VOC dataset could not be prepared.")
        
        # ✅ SQUARE CROP TRANSFORM: No distortion, preserves aspect ratio
        if image_set == 'train':
            self.transform = transforms_v2.Compose([
                # ✅ STEP 1: Square crop based on shorter side (random position)
                SquareCropTransform(random_crop=True),
                
                # ✅ STEP 2: Resize to target size without distortion
                transforms_v2.Resize((input_size, input_size)),
                
                # ✅ STEP 3: Augmentations
                transforms_v2.ColorJitter(brightness=0.1, contrast=0.1, saturation=0.1, hue=0.03),
                transforms_v2.RandomHorizontalFlip(p=0.5),
                
                # ✅ STEP 4: Normalization
                transforms_v2.ToImage(),
                transforms_v2.ToDtype(torch.float32, scale=True),
                transforms_v2.Normalize([0.485, 0.456, 0.406], [0.229, 0.224, 0.225])
            ])
        else:
            # ✅ VALIDATION: Center crop for consistent evaluation
            self.transform = transforms_v2.Compose([
                # ✅ STEP 1: Square crop based on shorter side (center position)
                SquareCropTransform(random_crop=False),
                
                # ✅ STEP 2: Resize to target size without distortion
                transforms_v2.Resize((input_size, input_size)),
                
                # ✅ STEP 3: Normalization
                transforms_v2.ToImage(),
                transforms_v2.ToDtype(torch.float32, scale=True),
                transforms_v2.Normalize([0.485, 0.456, 0.406], [0.229, 0.224, 0.225])
            ])
            
        # ✅ PERSON/CAT/DOG CLASSES: Most frequent in VOC dataset
        self.classes = {'person': 0, 'cat': 1, 'dog': 2}
        self.num_classes = len(self.classes)
        
        self.valid_idx = []
        for i in range(len(self.voc)):
            if self._has_target(i):
                self.valid_idx.append(i)
        print(f"Found {len(self.valid_idx)} valid images with person/cat/dog for {image_set}")
        print(f"✅ Using SQUARE CROP strategy for Person/Cat/Dog detection:")
        if image_set == 'train':
            print(f"  📏 Random square crop (shorter side) → Resize to {input_size}x{input_size}")
            print(f"  🎯 Benefits: No distortion, preserves aspect ratio, natural augmentation")
        else:
            print(f"  📏 Center square crop (shorter side) → Resize to {input_size}x{input_size}")
            print(f"  🎯 Consistent evaluation with no aspect ratio distortion")
        print(f"✅ Expected much better class balance: Person/Cat/Dog are top 3 most frequent!")
    
    def _has_target(self, idx):
        _, target = self.voc[idx]
        objects = target['annotation'].get('object', [])
        if isinstance(objects, dict):
            objects = [objects]
        for obj in objects:
            if obj['name'] in self.classes:
                return True
        return False

    def _extract_bboxes_and_classes(self, target):
        objects = target['annotation'].get('object', [])
        if isinstance(objects, dict):
            objects = [objects]
        bboxes = []
        class_labels = []
        for obj in objects:
            name = obj['name']
            if name in self.classes:
                bbox = obj['bndbox']
                x1, y1 = float(bbox['xmin']), float(bbox['ymin'])
                x2, y2 = float(bbox['xmax']), float(bbox['ymax'])
                bboxes.append([x1, y1, x2, y2])
                class_labels.append(self.classes[name])
        return bboxes, class_labels

    def _create_anchor_free_target_from_transformed_boxes(self, bboxes, class_labels, img_w, img_h):
        objectness_target = torch.zeros(self.grid_size, self.grid_size, 1)
        class_target = torch.zeros(self.grid_size, self.grid_size, self.num_classes)
        bbox_target = torch.zeros(self.grid_size, self.grid_size, 4)
        
        for bbox, class_label in zip(bboxes, class_labels):
            if hasattr(bbox, 'tolist'):
                x1, y1, x2, y2 = bbox.tolist()
            else:
                x1, y1, x2, y2 = bbox
            
            x1, y1, x2, y2 = max(0, x1), max(0, y1), min(img_w, x2), min(img_h, y2)
            if x2 <= x1 or y2 <= y1:
                continue
            
            center_x = (x1 + x2) / 2 / img_w
            center_y = (y1 + y2) / 2 / img_h
            width = (x2 - x1) / img_w
            height = (y2 - y1) / img_h
            
            center_x = max(0, min(1, center_x))
            center_y = max(0, min(1, center_y))
            width = max(0, min(1, width))
            height = max(0, min(1, height))
            
            grid_x = int(center_x * self.grid_size)
            grid_y = int(center_y * self.grid_size)
            grid_x = min(max(grid_x, 0), self.grid_size - 1)
            grid_y = min(max(grid_y, 0), self.grid_size - 1)
            
            objectness_target[grid_y, grid_x, 0] = 1.0
            class_target[grid_y, grid_x, class_label] = 1.0
            bbox_target[grid_y, grid_x, 0] = center_x
            bbox_target[grid_y, grid_x, 1] = center_y
            bbox_target[grid_y, grid_x, 2] = width
            bbox_target[grid_y, grid_x, 3] = height
        
        return objectness_target, class_target, bbox_target
    
    def __len__(self):
        return len(self.valid_idx)
    
    def __getitem__(self, idx):
        real_idx = self.valid_idx[idx]
        image, target = self.voc[real_idx]
        
        bboxes, class_labels = self._extract_bboxes_and_classes(target)
        
        if len(bboxes) == 0:
            image = self.transform(image)
            obj_target = torch.zeros(self.grid_size, self.grid_size, 1)
            cls_target = torch.zeros(self.grid_size, self.grid_size, self.num_classes)
            bbox_target = torch.zeros(self.grid_size, self.grid_size, 4)
            return image, obj_target, cls_target, bbox_target
        
        orig_width, orig_height = image.size
        boxes = BoundingBoxes(bboxes, format="XYXY", canvas_size=(orig_height, orig_width))
        sample = {"image": image, "boxes": boxes, "labels": torch.tensor(class_labels)}
        transformed = self.transform(sample)
        
        transformed_image = transformed["image"]
        transformed_boxes = transformed["boxes"]
        transformed_labels = transformed["labels"]
        transformed_bboxes = transformed_boxes.data.tolist()
        transformed_class_labels = transformed_labels.tolist()
        
        obj_target, cls_target, bbox_target = self._create_anchor_free_target_from_transformed_boxes(
            transformed_bboxes, transformed_class_labels, img_w=self.input_size, img_h=self.input_size
        )
        
        return transformed_image, obj_target, cls_target, bbox_target

# ==================== LOSS FUNCTIONS ====================
def focal_loss(pred, target, alpha=0.25, gamma=2.0):
    """Focal Loss for classification"""
    ce_loss = F.binary_cross_entropy_with_logits(pred, target, reduction='none')
    pt = torch.exp(-ce_loss)
    focal_loss = alpha * (1 - pt) ** gamma * ce_loss
    return focal_loss.mean()

def smooth_l1_loss(pred_bbox, target_bbox, mask, beta=0.1):
    """Smooth L1 Loss for bounding box regression"""
    if mask.sum() == 0:
        return torch.tensor(0.0, device=pred_bbox.device)
    
    pred_bbox = pred_bbox[mask]
    target_bbox = target_bbox[mask]
    
    diff = torch.abs(pred_bbox - target_bbox)
    loss = torch.where(diff < beta, 0.5 * diff ** 2 / beta, diff - 0.5 * beta)
    return loss.mean()

def efficient_bbox_loss(pred_bbox, target_bbox, mask):
    """Optimized bbox loss for EfficientNet"""
    if mask.sum() == 0:
        return torch.tensor(0.0, device=pred_bbox.device)
    
    pred_bbox_norm = torch.sigmoid(pred_bbox[mask])
    target_bbox_selected = target_bbox[mask]
    
    # Combine MSE and Smooth L1 for better convergence
    mse_loss = F.mse_loss(pred_bbox_norm, target_bbox_selected)
    smooth_l1_val = smooth_l1_loss(torch.sigmoid(pred_bbox), target_bbox, mask, beta=0.05)
    
    return 0.7 * mse_loss + 0.3 * smooth_l1_val

# ==================== TRAINING FUNCTION ====================
def train_person_cat_dog_model(model, train_loader, val_loader, num_epochs=12):
    # GPU optimization
    torch.backends.cudnn.benchmark = True
    torch.backends.cudnn.deterministic = False
    
    print("Starting Person/Cat/Dog EfficientNet-B3 Training...")
    print("🚀 Using pre-trained EfficientNet-B3 backbone!")
    print("✅ SQUARE CROP strategy for distortion-free image processing")
    print("✅ BALANCED CLASSES: Person/Cat/Dog are top 3 most frequent in VOC!")
    print("✅ Expected excellent performance across all classes")
    print("-" * 60)
    
    # ✅ EFFICIENTNET OPTIMIZED: Sophisticated learning rate strategy
    backbone_params = []
    head_params = []
    
    for name, param in model.named_parameters():
        if 'backbone' in name:
            backbone_params.append(param)
        else:
            head_params.append(param)
    
    # Fine-tuned learning rates for EfficientNet
    optimizer = optim.AdamW([
        {'params': backbone_params, 'lr': 0.00005, 'weight_decay': 1e-5},  # Very low for backbone
        {'params': head_params, 'lr': 0.001, 'weight_decay': 1e-4}         # Higher for heads
    ])
    
    # Cosine annealing with warm restarts
    scheduler = optim.lr_scheduler.CosineAnnealingWarmRestarts(
        optimizer, T_0=4, T_mult=2, eta_min=1e-7
    )
    scaler = torch.amp.GradScaler()
    
    best_loss = float('inf')
    
    for epoch in range(num_epochs):
        model.train()
        running_loss = 0.0
        running_obj_loss = 0.0
        running_cls_loss = 0.0
        running_bbox_loss = 0.0
        
        for batch_idx, (images, obj_targets, cls_targets, bbox_targets) in enumerate(train_loader):
            images = images.to(device, non_blocking=True)
            obj_targets = obj_targets.to(device, non_blocking=True)
            cls_targets = cls_targets.to(device, non_blocking=True)
            bbox_targets = bbox_targets.to(device, non_blocking=True)
            
            with torch.amp.autocast(device_type='cuda', dtype=torch.float16):
                optimizer.zero_grad()
                
                pred_obj, pred_cls, pred_bbox = model(images)
                
                # Balanced loss calculation - optimized for Person/Cat/Dog
                pos_weight = torch.tensor([6.0]).to(device)  # Reduced since classes are more balanced
                obj_loss = F.binary_cross_entropy_with_logits(
                    pred_obj, obj_targets, pos_weight=pos_weight
                )
                
                pos_mask = obj_targets.squeeze(-1) > 0.5
                if pos_mask.sum() > 0:
                    cls_loss = focal_loss(pred_cls[pos_mask], cls_targets[pos_mask])
                    bbox_loss = efficient_bbox_loss(pred_bbox, bbox_targets, pos_mask)
                else:
                    cls_loss = torch.tensor(0.0, device=device)
                    bbox_loss = torch.tensor(0.0, device=device)
                
                # Optimized loss weighting for balanced classes
                total_loss = 1.2 * obj_loss + cls_loss + 2.0 * bbox_loss
            
            scaler.scale(total_loss).backward()
            scaler.unscale_(optimizer)
            torch.nn.utils.clip_grad_norm_(model.parameters(), max_norm=0.5)
            scaler.step(optimizer)
            scaler.update()
            
            running_loss += total_loss.item()
            running_obj_loss += obj_loss.item()
            running_cls_loss += cls_loss.item()
            running_bbox_loss += bbox_loss.item()
            
            if batch_idx % 25 == 0:
                print(f'Epoch {epoch+1}, Batch {batch_idx}, '
                      f'Total: {total_loss.item():.4f}, '
                      f'Obj: {obj_loss.item():.4f}, '
                      f'Cls: {cls_loss.item():.4f}, '
                      f'BBox: {bbox_loss.item():.4f}')
        
        scheduler.step()
        
        epoch_loss = running_loss / len(train_loader)
        obj_avg = running_obj_loss / len(train_loader)
        cls_avg = running_cls_loss / len(train_loader)
        bbox_avg = running_bbox_loss / len(train_loader)
        
        print(f'Epoch [{epoch+1}/{num_epochs}] Average Losses:')
        print(f'  Total: {epoch_loss:.4f}, Obj: {obj_avg:.4f}, Cls: {cls_avg:.4f}, BBox: {bbox_avg:.4f}')
        print(f'  Backbone LR: {optimizer.param_groups[0]["lr"]:.7f}')
        print(f'  Heads LR: {optimizer.param_groups[1]["lr"]:.6f}')
        
        if epoch_loss < best_loss:
            best_loss = epoch_loss
            torch.save(model.state_dict(), 'efficientnet_b3_person_cat_dog_best.pth')
            print(f'  ✅ New best Person/Cat/Dog model saved! Loss: {best_loss:.4f}')
        
        # Early performance check
        if epoch == 2:
            print(f"\n🔍 EARLY PERSON/CAT/DOG CHECK:")
            model.eval()
            with torch.no_grad():
                for images, _, _, _ in val_loader:
                    images = images.to(device)
                    pred_obj, _, _ = model(images)
                    max_conf = torch.sigmoid(pred_obj).max().item()
                    print(f"  Max confidence after 3 epochs: {max_conf:.4f}")
                    if max_conf > 0.4:
                        print("  🚀 Excellent progress with balanced classes!")
                    elif max_conf > 0.2:
                        print("  ✅ Good learning progress")
                    else:
                        print("  ⚠️ Slower than expected")
                    break
            model.train()
        
        print("-" * 40)
    
    print("Person/Cat/Dog EfficientNet-B3 training completed!")
    return model

# ==================== EVALUATION FUNCTIONS ====================
def decode_predictions(objectness, classification, bbox_regression, 
                      conf_threshold=0.4, grid_size=13, img_size=224):
    """Decode predictions with optimized threshold"""
    detections = []
    
    for i in range(grid_size):
        for j in range(grid_size):
            obj_conf = torch.sigmoid(objectness[0, i, j, 0]).item()
            
            if obj_conf > conf_threshold:
                class_probs = torch.sigmoid(classification[0, i, j]).cpu().numpy()
                class_id = np.argmax(class_probs)
                class_conf = class_probs[class_id]
                
                bbox_raw = bbox_regression[0, i, j]
                center_x = torch.sigmoid(bbox_raw[0]).item()
                center_y = torch.sigmoid(bbox_raw[1]).item()
                width = torch.sigmoid(bbox_raw[2]).item()
                height = torch.sigmoid(bbox_raw[3]).item()
                
                center_x_px = center_x * img_size
                center_y_px = center_y * img_size
                width_px = width * img_size
                height_px = height * img_size
                
                x1 = center_x_px - width_px / 2
                y1 = center_y_px - height_px / 2
                x2 = center_x_px + width_px / 2
                y2 = center_y_px + height_px / 2
                
                x1 = max(0, min(img_size, x1))
                y1 = max(0, min(img_size, y1))
                x2 = max(0, min(img_size, x2))
                y2 = max(0, min(img_size, y2))
                
                total_conf = obj_conf * class_conf
                detections.append([x1, y1, x2, y2, total_conf, class_id])
    
    return detections

def non_max_suppression(detections, conf_threshold=0.5, iou_threshold=0.45):
    """NMS with optimized parameters"""
    if len(detections) == 0:
        return []
    
    detections = [det for det in detections if det[4] >= conf_threshold]
    if len(detections) == 0:
        return []
    
    detections.sort(key=lambda x: x[4], reverse=True)
    
    keep = []
    while detections:
        current = detections.pop(0)
        keep.append(current)
        
        remaining = []
        for det in detections:
            iou = calculate_iou(current[:4], det[:4])
            if iou <= iou_threshold:
                remaining.append(det)
        
        detections = remaining
    
    return keep

def calculate_iou(box1, box2):
    """Calculate IoU between two boxes"""
    x1 = max(box1[0], box2[0])
    y1 = max(box1[1], box2[1])
    x2 = min(box1[2], box2[2])
    y2 = min(box1[3], box2[3])
    
    if x2 <= x1 or y2 <= y1:
        return 0
    
    intersection = (x2 - x1) * (y2 - y1)
    area1 = (box1[2] - box1[0]) * (box1[3] - box1[1])
    area2 = (box2[2] - box2[0]) * (box2[3] - box2[1])
    union = area1 + area2 - intersection
    
    return intersection / union if union > 0 else 0

def calculate_ap(pred_boxes, pred_scores, gt_boxes, iou_threshold=0.5):
    """Calculate Average Precision"""
    if len(pred_boxes) == 0:
        return 0.0
    if len(gt_boxes) == 0:
        return 0.0
    
    sorted_indices = np.argsort(pred_scores)[::-1]
    pred_boxes = [pred_boxes[i] for i in sorted_indices]
    pred_scores = [pred_scores[i] for i in sorted_indices]
    
    tp = np.zeros(len(pred_boxes))
    fp = np.zeros(len(pred_boxes))
    gt_used = [False] * len(gt_boxes)
    
    for i, pred_box in enumerate(pred_boxes):
        best_iou = 0
        best_gt_idx = -1
        
        for j, gt_box in enumerate(gt_boxes):
            if gt_used[j]:
                continue
            iou = calculate_iou(pred_box, gt_box)
            if iou > best_iou:
                best_iou = iou
                best_gt_idx = j
        
        if best_iou >= iou_threshold and best_gt_idx != -1:
            tp[i] = 1
            gt_used[best_gt_idx] = True
        else:
            fp[i] = 1
    
    cumulative_tp = np.cumsum(tp)
    cumulative_fp = np.cumsum(fp)
    
    recall = cumulative_tp / len(gt_boxes)
    precision = cumulative_tp / (cumulative_tp + cumulative_fp + 1e-6)
    
    ap = 0
    for r in np.arange(0, 1.1, 0.1):
        p_vals = precision[recall >= r]
        p_max = np.max(p_vals) if len(p_vals) > 0 else 0
        ap += p_max / 11
    
    return ap

def evaluate_person_cat_dog_model(model, test_loader, conf_threshold=0.4):
    """Evaluate Person/Cat/Dog model"""
    print("\n" + "="*60)
    print("EVALUATING PERSON/CAT/DOG EFFICIENTNET-B3 MODEL")
    print("="*60)
    
    model.eval()
    class_names = ['person', 'cat', 'dog']
    
    all_predictions = {0: {'boxes': [], 'scores': []}, 1: {'boxes': [], 'scores': []}, 2: {'boxes': [], 'scores': []}}
    all_ground_truths = {0: [], 1: [], 2: []}
    
    total_images = 0
    total_detections = 0
    
    with torch.no_grad():
        for batch_idx, (images, obj_targets, cls_targets, bbox_targets) in enumerate(test_loader):
            if batch_idx >= 50:  # Test on subset
                break
                
            images = images.to(device)
            pred_obj, pred_cls, pred_bbox = model(images)
            
            for img_idx in range(len(images)):
                total_images += 1
                
                detections_raw = decode_predictions(
                    pred_obj[img_idx:img_idx+1], pred_cls[img_idx:img_idx+1], 
                    pred_bbox[img_idx:img_idx+1], conf_threshold=conf_threshold
                )
                
                detections = non_max_suppression(detections_raw, 
                                               conf_threshold=conf_threshold, 
                                               iou_threshold=0.45)
                
                total_detections += len(detections)
                
                for det in detections:
                    x1, y1, x2, y2, conf, class_id = det
                    class_id = int(class_id)
                    all_predictions[class_id]['boxes'].append([x1, y1, x2, y2])
                    all_predictions[class_id]['scores'].append(conf)
                
                # Extract ground truth
                obj_mask = obj_targets[img_idx].squeeze(-1) > 0.5
                if obj_mask.sum() > 0:
                    gt_indices = torch.where(obj_mask)
                    for i in range(len(gt_indices[0])):
                        row, col = gt_indices[0][i].item(), gt_indices[1][i].item()
                        class_probs = cls_targets[img_idx, row, col]
                        gt_class = torch.argmax(class_probs).item()
                        
                        center_x = bbox_targets[img_idx, row, col, 0].item() * 224
                        center_y = bbox_targets[img_idx, row, col, 1].item() * 224
                        width = bbox_targets[img_idx, row, col, 2].item() * 224
                        height = bbox_targets[img_idx, row, col, 3].item() * 224
                        
                        x1 = center_x - width / 2
                        y1 = center_y - height / 2
                        x2 = center_x + width / 2
                        y2 = center_y + height / 2
                        
                        all_ground_truths[gt_class].append([x1, y1, x2, y2])
    
    print(f"Total images processed: {total_images}")
    print(f"Total detections made: {total_detections}")
    print(f"Average detections per image: {total_detections/total_images:.2f}")
    
    overall_ap = []
    for class_id in [0, 1, 2]:
        class_name = class_names[class_id]
        n_pred = len(all_predictions[class_id]['boxes'])
        n_gt = len(all_ground_truths[class_id])
        
        print(f"\n{class_name.upper()}:")
        print(f"  Predictions: {n_pred}")
        print(f"  Ground truth: {n_gt}")
        
        if n_gt > 0 and n_pred > 0:
            ap = calculate_ap(
                all_predictions[class_id]['boxes'],
                all_predictions[class_id]['scores'],
                all_ground_truths[class_id],
                iou_threshold=0.5
            )
            overall_ap.append(ap)
            print(f"  Average Precision (AP@0.5): {ap:.4f}")
        else:
            print(f"  Average Precision (AP@0.5): 0.0000")
            overall_ap.append(0.0)
    
    mean_ap = np.mean(overall_ap)
    print(f"\nOVERALL PERFORMANCE:")
    print(f"Mean Average Precision (mAP@0.5): {mean_ap:.4f}")
    
    return mean_ap, overall_ap

# ==================== VISUALIZATION FUNCTION ====================
def visualize_random_predictions(model, loader, num_images=10, conf_threshold=0.5):
    """모델의 예측 결과를 랜덤 이미지에 바운딩 박스로 그려서 보여줍니다."""
    print("\n" + "="*60)
    print("🔍 VISUALIZING RANDOM PREDICTIONS")
    print("="*60)
    
    model.eval()
    dataset = loader.dataset
    class_names = {v: k for k, v in dataset.classes.items()}
    colors = ['r', 'g', 'b']

    # 시각화를 위해 랜덤으로 이미지 인덱스 선택
    indices = np.random.choice(len(dataset), num_images, replace=False)
    
    # Matplotlib figure 설정
    plt.figure(figsize=(20, 15))
    
    with torch.no_grad():
        for i, idx in enumerate(indices):
            # 데이터셋에서 이미지와 타겟 가져오기
            image_tensor, _, _, _ = dataset[idx]
            
            # 모델 입력을 위해 배치 차원 추가 및 디바이스로 이동
            input_tensor = image_tensor.unsqueeze(0).to(device)
            
            # 모델 예측
            pred_obj, pred_cls, pred_bbox = model(input_tensor)
            
            # 예측 결과 디코딩 및 NMS 적용
            detections_raw = decode_predictions(
                pred_obj, pred_cls, pred_bbox, conf_threshold=conf_threshold
            )
            final_detections = non_max_suppression(
                detections_raw, conf_threshold=conf_threshold, iou_threshold=0.45
            )

            # --- 시각화를 위해 이미지 텐서 변환 ---
            # 1. Denormalize (정규화 해제)
            mean = torch.tensor([0.485, 0.456, 0.406]).view(3, 1, 1)
            std = torch.tensor([0.229, 0.224, 0.225]).view(3, 1, 1)
            img_display = image_tensor.cpu().clone()
            img_display = img_display * std + mean
            
            # 2. 텐서 차원 변경 (C, H, W) -> (H, W, C) for Matplotlib
            img_display = img_display.permute(1, 2, 0).numpy()
            img_display = np.clip(img_display, 0, 1) # 픽셀 값을 0과 1 사이로 조정

            # --- 이미지와 바운딩 박스 그리기 ---
            ax = plt.subplot(2, 5, i + 1)
            ax.imshow(img_display)
            ax.axis('off')

            if not final_detections:
                ax.set_title("No Detections")
                continue

            for det in final_detections:
                x1, y1, x2, y2, conf, class_id = det
                class_id = int(class_id)
                
                # 박스 그리기
                rect = patches.Rectangle(
                    (x1, y1), x2 - x1, y2 - y1,
                    linewidth=2,
                    edgecolor=colors[class_id],
                    facecolor='none'
                )
                ax.add_patch(rect)
                
                # 클래스 이름과 신뢰도 표시
                label = f"{class_names[class_id]}: {conf:.2f}"
                ax.text(
                    x1, y1 - 5, label,
                    color='white',
                    fontsize=10,
                    bbox=dict(facecolor=colors[class_id], alpha=0.7)
                )
            ax.set_title(f"Image {idx}")

    plt.tight_layout()
    print("✅ Plotting predictions. Please close the plot window to exit.")
    plt.show(block=True) # 창을 닫을 때까지 프로그램이 멈추도록 설정

# ==================== MAIN SCRIPT ====================
def main():
    # --- Hyperparameters ---
    BATCH_SIZE = 16
    NUM_EPOCHS = 12
    GRID_SIZE = 13
    INPUT_SIZE = 300  # EfficientNet-B3 optimal input size

    print("=" * 60)
    print("🚀 INITIALIZING PERSON/CAT/DOG DETECTION PIPELINE 🚀")
    print(f"Device: {device}")
    print(f"Batch Size: {BATCH_SIZE}, Epochs: {NUM_EPOCHS}, Input Size: {INPUT_SIZE}x{INPUT_SIZE}")
    print("=" * 60)
    
    # --- Datasets and DataLoaders ---
    print("\n[PHASE 1] Loading Datasets...")
    start_time = time.time()
    
    # Training dataset
    train_dataset = PersonCatDogVOCDataset(image_set='train', grid_size=GRID_SIZE, input_size=INPUT_SIZE)
    train_loader = DataLoader(
        train_dataset, 
        batch_size=BATCH_SIZE, 
        shuffle=True, 
        num_workers=4,
        pin_memory=True
    )
    
    # Validation dataset
    val_dataset = PersonCatDogVOCDataset(image_set='val', grid_size=GRID_SIZE, input_size=INPUT_SIZE)
    val_loader = DataLoader(
        val_dataset, 
        batch_size=BATCH_SIZE, 
        shuffle=False, 
        num_workers=4,
        pin_memory=True
    )
    
    end_time = time.time()
    print(f"✅ Datasets loaded successfully in {end_time - start_time:.2f} seconds.")

    # --- Model Initialization ---
    print("\n[PHASE 2] Initializing Model...")
    model = EfficientNetDetector(num_classes=train_dataset.num_classes, grid_size=GRID_SIZE)
    model.to(device)
    print("✅ Model initialized and moved to device.")

    # --- Training ---
    print("\n[PHASE 3] Starting Model Training...")
    start_time = time.time()
    
    trained_model = train_person_cat_dog_model(model, train_loader, val_loader, num_epochs=NUM_EPOCHS)
    
    end_time = time.time()
    print(f"✅ Training completed in {(end_time - start_time) / 60:.2f} minutes.")

    # --- Evaluation ---
    print("\n[PHASE 4] Evaluating Best Model...")
    
    best_model = EfficientNetDetector(num_classes=train_dataset.num_classes, grid_size=GRID_SIZE)
    best_model.load_state_dict(torch.load('efficientnet_b3_person_cat_dog_best.pth'))
    best_model.to(device)
    
    start_time = time.time()
    
    mean_ap, _ = evaluate_person_cat_dog_model(best_model, val_loader, conf_threshold=0.4)
    
    end_time = time.time()
    print(f"✅ Evaluation completed in {end_time - start_time:.2f} seconds.")
    print("\n" + "🎉" * 20)
    print(f"FINAL RESULT: mAP@0.5 = {mean_ap:.4f}")
    print("🎉" * 20)

    # --- ✨ NEW: VISUALIZATION PHASE ✨ ---
    visualize_random_predictions(best_model, val_loader, num_images=10)


if __name__ == '__main__':
    main()