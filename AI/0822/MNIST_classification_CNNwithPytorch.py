import torch
import torch.nn as nn
import torch.optim as optim
import torch.nn.functional as F
from torch.utils.data import DataLoader
import torchvision
import torchvision.transforms as transforms
import matplotlib.pyplot as plt
import numpy as np

device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
print(f'Using device: {device}')

class MNISTNet_CNN(nn.Module):
    def __init__(self, input_size=784, hidden_sizes=[512, 256, 128], num_classes=10):
        super(MNISTNet_CNN, self).__init__()
        
        # Convolutional Block 1, 1채널(그레이스케일) → 32채널
        # 3x3 커널 + same padding(=1)으로 해상도 유지, 이후 MaxPool로 1/2 다운샘플(28→14)
        self.conv1 = nn.Conv2d(1, 32, kernel_size=3, padding=1)  # 28x28 -> 28x28
        self.bn1 = nn.BatchNorm2d(32) # 학습 안정화 및 수렴 가속
        self.pool1 = nn.MaxPool2d(2, 2)  # 28x28 -> 14x14, 다운샘플로 연산량↓, 수용영역↑
        
        # Convolutional Block 2, 32채널 → 64채널, 14→7로 다운샘플
        self.conv2 = nn.Conv2d(32, 64, kernel_size=3, padding=1)  # 14x14 -> 14x14
        self.bn2 = nn.BatchNorm2d(64)
        self.pool2 = nn.MaxPool2d(2, 2)  # 14x14 -> 7x7
        
        # Convolutional Block 3, 64채널 → 128채널, 7→3으로 다운샘플
        self.conv3 = nn.Conv2d(64, 128, kernel_size=3, padding=1)  # 7x7 -> 7x7
        self.bn3 = nn.BatchNorm2d(128)
        self.pool3 = nn.MaxPool2d(2, 2)  # 7x7 -> 3x3
        
        # Calculate the size after convolutions: 128 * 3 * 3 = 1152
        self.fc1 = nn.Linear(128 * 3 * 3, 256)
        self.bn4 = nn.BatchNorm1d(256)
        self.fc2 = nn.Linear(256, num_classes)
        
        # Dropout layers
        self.dropout1 = nn.Dropout2d(0.25)  # 2D dropout for conv layers
        self.dropout2 = nn.Dropout2d(0.25)
        self.dropout3 = nn.Dropout(0.5)     # 1D dropout for FC layers
        
        self._initialize_weights()
    
    def _initialize_weights(self):
        """ Linear 계층만 Xavier로 초기화(Conv는 PyTorch 기본값 유지) """
        for module in self.modules():
            if isinstance(module, nn.Linear):
                nn.init.xavier_uniform_(module.weight)
                nn.init.constant_(module.bias, 0)
    
    def forward(self, x):
        # Convolutional Block 1
        x = self.conv1(x)
        x = self.bn1(x)
        x = F.relu(x)
        x = self.pool1(x)
        x = self.dropout1(x)
        
        # Convolutional Block 2
        x = self.conv2(x)
        x = self.bn2(x)
        x = F.relu(x)
        x = self.pool2(x)
        x = self.dropout2(x)
        
        # Convolutional Block 3
        x = self.conv3(x)
        x = self.bn3(x)
        x = F.relu(x)
        x = self.pool3(x)
        
        # Flatten and fully connected layers
        x = x.view(x.size(0), -1)  # Flatten: [batch_size, 128*3*3]
        x = self.fc1(x)
        x = self.bn4(x)
        x = F.relu(x)
        x = self.dropout3(x)
        x = self.fc2(x)
        
        # NLLLoss와 궁합 맞추기 위해 log_softmax 출력
        return F.log_softmax(x, dim=1)

def prepare_data():
    """ 텐서화 + 정규화(평균/표준편차는 MNIST/FashionMNIST 관습적 값) """
    transform = transforms.Compose([
        transforms.ToTensor(),
        transforms.Normalize((0.1307,), (0.3081,))
    ])
    
    # 데이터셋: FashionMNIST (MNIST로 교체 가능)
    # train_dataset = torchvision.datasets.MNIST(
    train_dataset = torchvision.datasets.FashionMNIST(
        root='./data', 
        train=True, 
        download=True, 
        transform=transform
    )
    # test_dataset = torchvision.datasets.MNIST(
    test_dataset = torchvision.datasets.FashionMNIST(
        root='./data', 
        train=False, 
        download=True, 
        transform=transform
    )
    
    # DataLoader: 학습은 셔플, 테스트는 고정
    train_loader = DataLoader(
        train_dataset, 
        batch_size=128, 
        shuffle=True,
        num_workers=2
    )
    test_loader = DataLoader(
        test_dataset, 
        batch_size=1000, 
        shuffle=False,
        num_workers=2
    )
    
    return train_loader, test_loader

def train_model(model, train_loader, test_loader, num_epochs=15):
    criterion = nn.NLLLoss()
    optimizer = optim.Adam(model.parameters(), lr=0.001, weight_decay=1e-4)
    scheduler = optim.lr_scheduler.StepLR(optimizer, step_size=5, gamma=0.5)
    
    train_losses = []
    train_accuracies = []
    test_accuracies = []
    
    print("Starting CNN training...")
    print("-" * 60)
    
    for epoch in range(num_epochs):
        model.train() # BN/Dropout 학습 모드
        running_loss = 0.0
        correct = 0
        total = 0
        
        for batch_idx, (data, target) in enumerate(train_loader):
            data, target = data.to(device), target.to(device)
            
            optimizer.zero_grad()
            
            output = model(data) # 순전파
            loss = criterion(output, target) # 손실
            
            loss.backward() # 역전파
            optimizer.step() # 파라미터 갱신
            
            # 통계 집계
            running_loss += loss.item()
            pred = output.argmax(dim=1, keepdim=True)
            correct += pred.eq(target.view_as(pred)).sum().item()
            total += target.size(0)
            
            if batch_idx % 100 == 0:
                print(f'Epoch: {epoch+1}/{num_epochs}, Batch: {batch_idx}/{len(train_loader)}, '
                      f'Loss: {loss.item():.6f}, Accuracy: {100.*correct/total:.2f}%')
        
        # 에폭 요약 및 검증(여기서는 test를 간이 검증으로 사용)
        epoch_loss = running_loss / len(train_loader)
        epoch_accuracy = 100. * correct / total
        train_losses.append(epoch_loss)
        train_accuracies.append(epoch_accuracy)
        
        # 주의: 엄밀한 일반화 평가는 별도의 val_loader를 두는 것을 권장
        test_accuracy = test_model(model, test_loader, verbose=False)
        test_accuracies.append(test_accuracy)
        
        scheduler.step() # step_size마다 lr 감소
        
        print(f'Epoch [{epoch+1}/{num_epochs}] Summary:')
        print(f'  Train Loss: {epoch_loss:.4f}, Train Acc: {epoch_accuracy:.2f}%, Test Acc: {test_accuracy:.2f}%')
        print(f'  Learning Rate: {scheduler.get_last_lr()[0]:.6f}')
        print("-" * 60)
    
    return train_losses, train_accuracies, test_accuracies

def test_model(model, test_loader, verbose=True):
    model.eval() # BN/Dropout 평가 모드
    test_loss = 0
    correct = 0
    
    with torch.no_grad(): # 평가 시 그래디언트 계산 비활성화
        for data, target in test_loader:
            data, target = data.to(device), target.to(device)
            output = model(data)
            test_loss += F.nll_loss(output, target, reduction='sum').item()
            pred = output.argmax(dim=1, keepdim=True)
            correct += pred.eq(target.view_as(pred)).sum().item()
    
    test_loss /= len(test_loader.dataset)
    accuracy = 100. * correct / len(test_loader.dataset)
    
    if verbose:
        print(f'Test Results:')
        print(f'  Average loss: {test_loss:.4f}')
        print(f'  Accuracy: {correct}/{len(test_loader.dataset)} ({accuracy:.2f}%)')
    
    return accuracy

def visualize_predictions(model, test_loader, num_images=8):
    """ 테스트 샘플 일부에 대해 정답/예측/신뢰도 시각화 """
    model.eval()
    
    data_iter = iter(test_loader)
    images, labels = next(data_iter)
    images, labels = images.to(device), labels.to(device)
    
    with torch.no_grad():
        outputs = model(images[:num_images])
        predictions = outputs.argmax(dim=1)
        probabilities = torch.exp(outputs) # log_softmax → 확률로 변환
    
    fig, axes = plt.subplots(2, 4, figsize=(12, 6))
    axes = axes.ravel()
    
    for i in range(num_images):
        img = images[i].cpu().squeeze()
        true_label = labels[i].cpu().item()
        pred_label = predictions[i].cpu().item()
        confidence = probabilities[i][pred_label].cpu().item()
        
        axes[i].imshow(img, cmap='gray')
        color = 'green' if true_label == pred_label else 'red'
        axes[i].set_title(f'True: {true_label}, Pred: {pred_label}\nConf: {confidence:.3f}', 
                         color=color, fontsize=10)
        axes[i].axis('off')
    
    plt.tight_layout()
    plt.show()

def analyze_network_weights(model):
    """ 각 계층 가중치 분포(평균/표준편차 등)로 학습 상태 체크 """
    print("Network Weight Analysis")
    print("-" * 50)
    
    layer_names = []
    weight_means = []
    weight_stds = []
    
    for name, param in model.named_parameters():
        if 'weight' in name and param.dim() >= 2:
            layer_names.append(name)
            weight_means.append(param.data.mean().item())
            weight_stds.append(param.data.std().item())
            
            print(f"Layer: {name}")
            print(f"  Shape: {param.shape}")
            print(f"  Mean: {param.data.mean().item():.6f}")
            print(f"  Std: {param.data.std().item():.6f}")
            print(f"  Min: {param.data.min().item():.6f}")
            print(f"  Max: {param.data.max().item():.6f}")
            print()
    
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 4))
    
    x_pos = range(len(layer_names))
    
    ax1.bar(x_pos, weight_means)
    ax1.set_title('Weight Means by Layer')
    ax1.set_xlabel('Layer')
    ax1.set_ylabel('Mean Weight Value')
    ax1.set_xticks(x_pos)
    ax1.set_xticklabels([name.split('.')[0] for name in layer_names], rotation=45)
    
    ax2.bar(x_pos, weight_stds)
    ax2.set_title('Weight Standard Deviations by Layer')
    ax2.set_xlabel('Layer')
    ax2.set_ylabel('Weight Std')
    ax2.set_xticks(x_pos)
    ax2.set_xticklabels([name.split('.')[0] for name in layer_names], rotation=45)
    
    plt.tight_layout()
    plt.show()

def plot_training_history(train_losses, train_accuracies, test_accuracies):
    """ 학습 곡선: 과적합 여부/수렴 판단에 활용 """
    epochs = range(1, len(train_losses) + 1)
    
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 4))
    
    ax1.plot(epochs, train_losses, 'b-', label='Training Loss', linewidth=2)
    ax1.set_title('Training Loss (CNN)')
    ax1.set_xlabel('Epoch')
    ax1.set_ylabel('Loss')
    ax1.legend()
    ax1.grid(True, alpha=0.3)
    
    ax2.plot(epochs, train_accuracies, 'b-', label='Training Accuracy', linewidth=2)
    ax2.plot(epochs, test_accuracies, 'r-', label='Test Accuracy', linewidth=2)
    ax2.set_title('Model Accuracy (CNN)')
    ax2.set_xlabel('Epoch')
    ax2.set_ylabel('Accuracy (%)')
    ax2.legend()
    ax2.grid(True, alpha=0.3)
    
    plt.tight_layout()
    plt.show()

def compare_model_complexities():
    """ 파라미터/모델 크기 비교 유틸(빠른 규모 감) """
    print("Comparing CNN Model Complexities")
    print("-" * 60)
    
    models = {
        'Standard CNN': MNISTNet_CNN(),
        'Deep CNN': MNISTNet_CNN(hidden_sizes=[1024, 512, 256, 128]) # FC 너비만 확장한 변형
    }
    
    for name, model in models.items():
        total_params = sum(p.numel() for p in model.parameters())
        trainable_params = sum(p.numel() for p in model.parameters() if p.requires_grad)
        
        print(f"{name}:")
        print(f"  Total parameters: {total_params:,}")
        print(f"  Trainable parameters: {trainable_params:,}")
        print(f"  Model size (MB): {total_params * 4 / 1024 / 1024:.2f}") # FP32 기준
        print()

def save_model(model, filepath='mnist_cnn_model.pth'):
    """ state_dict + 간단 메타 저장 """
    torch.save({
        'model_state_dict': model.state_dict(),
        'model_type': type(model).__name__,
        'input_size': 784,
        'num_classes': 10
    }, filepath)
    print(f'CNN model saved to {filepath}')

def load_model(filepath='mnist_cnn_model.pth'):
    """ 동일 구조로 로드 후 eval 모드 """
    checkpoint = torch.load(filepath, map_location=device)
    
    model = MNISTNet_CNN().to(device)
    model.load_state_dict(checkpoint['model_state_dict'])
    model.eval()
    print(f'CNN model loaded from {filepath}')
    return model

def main():
    print("=== MNIST Handwritten Digit Classification with CNN ===")
    print("=== CNN을 사용한 MNIST 손글씨 숫자 분류 ===\n")
    
    # 데이터 준비 및 샘플 수 출력
    print("Preparing data...")
    train_loader, test_loader = prepare_data()
    print(f"Training samples: {len(train_loader.dataset)}")
    print(f"Test samples: {len(test_loader.dataset)}\n")
    
    # 간단한 모델 규모 비교(옵션)
    compare_model_complexities()
    
    print("Creating CNN model...")
    model = MNISTNet_CNN().to(device)
    
    print("Model Architecture:")
    print(model)
    
    total_params = sum(p.numel() for p in model.parameters())
    trainable_params = sum(p.numel() for p in model.parameters() if p.requires_grad)
    print(f"\nTotal parameters: {total_params:,}")
    print(f"Trainable parameters: {trainable_params:,}")
    print(f"Model size: {total_params * 4 / 1024 / 1024:.2f} MB\n")
    
    train_losses, train_accs, test_accs = train_model(model, train_loader, test_loader, num_epochs=15)
    
    print("\n=== Final Test Results ===")
    final_accuracy = test_model(model, test_loader)
    
    analyze_network_weights(model)
    
    plot_training_history(train_losses, train_accs, test_accs)
    
    visualize_predictions(model, test_loader)
    
    save_model(model)
    
    print(f"\nCNN training completed! Final accuracy: {final_accuracy:.2f}%")
    print("CNN 훈련 완료! 최종 정확도:", f"{final_accuracy:.2f}%")

if __name__ == "__main__":
    main()