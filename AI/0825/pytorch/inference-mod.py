import torch
import torchvision.transforms as transforms
from PIL import Image
import os
import pickle
from torchvision import models

def load_images_in_folder(folder):
    images = []
    filenames = []

    transform = transforms.Compose([
        transforms.Resize((224, 224)),
        transforms.ToTensor()
    ])

    for file in os.listdir(folder):
        path = os.path.join(folder, file)
        try:
            img = Image.open(path).convert("RGB")
            img_tensor = transform(img)
            images.append(img_tensor)
            filenames.append(file)
        except Exception as e:
            print(f"Error loading {file}: {e}")

    if images:
        images = torch.stack(images)  # Shape: (N, 3, 224, 224)
    else:
        images = torch.empty((0, 3, 224, 224))

    return images, filenames

def inference():
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

    # Load class labels
    with open("class_names.pkl", "rb") as f:
        class_names = pickle.load(f)
    label_map = {name: idx for idx, name in enumerate(class_names)}
    id_to_label = {v: k for k, v in label_map.items()}
    num_classes = len(class_names)

    # Load model
    model = models.mobilenet_v2(weights=None)
    model.classifier[1] = torch.nn.Linear(model.classifier[1].in_features, num_classes)
    model.load_state_dict(torch.load("best_mobilenetv2.pth", map_location=device))
    model.to(device)
    model.eval()

    test_root = "dataset/test"
    total_correct = 0
    total_samples = 0

    print("Detailed Inference Results\n==========================")

    for class_name in sorted(os.listdir(test_root)):
        folder = os.path.join(test_root, class_name)
        if not os.path.isdir(folder): continue

        X, filenames = load_images_in_folder(folder)
        if len(X) == 0:
            print(f"\n{class_name}: No images found.\n")
            continue

        X = X.to(device)
        with torch.no_grad():
            outputs = model(X)
            preds = torch.argmax(outputs, dim=1).cpu().numpy()

        true_label = label_map[class_name]

        print(f"\nClass: {class_name}")
        print("-" * 40)
        correct = 0
        for i, pred in enumerate(preds):
            pred_label = id_to_label[pred]
            is_correct = pred == true_label
            mark = "✔️" if is_correct else "❌"
            print(f"{filenames[i]:25} → Predicted: {pred_label:15} {mark}")
            if is_correct:
                correct += 1

        total = len(preds)
        acc = correct / total * 100
        print(f"\n{class_name} Accuracy: {acc:.2f}% ({correct}/{total})")

        total_correct += correct
        total_samples += total

    print("\n==========================")
    print(f"Overall Accuracy : {total_correct / total_samples * 100:.2f}% ({total_correct}/{total_samples})")

if __name__ == "__main__":
    inference()

