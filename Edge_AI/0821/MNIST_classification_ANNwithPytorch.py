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

class MNISTNet_ANN(nn.Module):
    def __init__(self, input_size=784, hidden_size=256, num_classes=10):
        super(MNISTNet_ANN, self).__init__()
        self.flatten = nn.Flatten()
        self.fc1 = nn.Linear(input_size, hidden_size)
        self.fc2 = nn.Linear(hidden_size, num_classes)
        
        self._initialize_weights()
    
    def _initialize_weights(self):
        for module in self.modules():
            if isinstance(module, nn.Linear):
                nn.init.uniform_(module.weight, -0.001, 0.001)
                '''
                Select Method for initiate weight value
                '''
                
                # nn.init.constant_(module.weight, 0.01)
                # nn.init.uniform_(module.weight, -1.0, 1.0)
                # nn.init.normal_(module.weight, mean=0, std=1.0)
                # nn.init.normal_(module.weight, mean=0, std=0.05)
                nn.init.constant_(module.bias, 0)
    
    def forward(self, x):
        x = self.flatten(x)
        x = self.fc1(x)
        x = F.relu(x)
        x = self.fc2(x)
        
        return x

def prepare_data():

    '''
    transform = transforms.Compose([
        transforms.ToTensor(),
        transforms.Normalize((0.1307,), (0.3081,))
    ])
    '''
    
    train_dataset = torchvision.datasets.MNIST(
        root='./data', 
        train=True, 
        download=True, 
        transform=transforms.ToTensor()
    )
    
    test_dataset = torchvision.datasets.MNIST(
        root='./data', 
        train=False, 
        download=True, 
        transform=transforms.ToTensor()
    )
    
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
    criterion = nn.CrossEntropyLoss()
    optimizer = optim.SGD(model.parameters(), lr=0.01)
    # optimizer = optim.Adam(model.parameters(), lr=0.001, weight_decay=1e-4)
    # scheduler = optim.lr_scheduler.StepLR(optimizer, step_size=5, gamma=0.5)
    
    train_losses = []
    train_accuracies = []
    test_accuracies = []
    
    print("Starting ANN training...")
    print("-" * 60)
    
    for epoch in range(num_epochs):
        model.train()
        running_loss = 0.0
        correct = 0
        total = 0
        
        for batch_idx, (data, target) in enumerate(train_loader):
            data, target = data.to(device), target.to(device)
            
            # 1. Clear leftover gradients from previous iteration
            optimizer.zero_grad()
            # 2. Forward pass: Build computational graph + map dependencies  
            output = model(data)
            loss = criterion(output, target)
            # 3. Backward pass: Use the graph to compute gradients
            loss.backward()
            # Apply gradients 
            optimizer.step()
            
            running_loss += loss.item()
            pred = output.argmax(dim=1, keepdim=True)
            correct += pred.eq(target.view_as(pred)).sum().item()
            total += target.size(0)
            
            if batch_idx % 100 == 0:
                print(f'Epoch: {epoch+1}/{num_epochs}, Batch: {batch_idx}/{len(train_loader)}, '
                      f'Loss: {loss.item():.6f}, Accuracy: {100.*correct/total:.2f}%')
        
        epoch_loss = running_loss / len(train_loader)
        epoch_accuracy = 100. * correct / total
        train_losses.append(epoch_loss)
        train_accuracies.append(epoch_accuracy)
        
        test_accuracy = test_model(model, test_loader, verbose=False)
        test_accuracies.append(test_accuracy)
        
        print(f'Epoch [{epoch+1}/{num_epochs}] Summary:')
        print(f'  Train Loss: {epoch_loss:.4f}, Train Acc: {epoch_accuracy:.2f}%, Test Acc: {test_accuracy:.2f}%')
        print("-" * 60)
    
    return train_losses, train_accuracies, test_accuracies

def test_model(model, test_loader, verbose=True):
    model.eval()
    test_loss = 0
    correct = 0
    
    with torch.no_grad():
        for data, target in test_loader:
            data, target = data.to(device), target.to(device)
            output = model(data)
            test_loss += F.cross_entropy(output, target, reduction='sum').item()
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
    model.eval()
    
    data_iter = iter(test_loader)
    images, labels = next(data_iter)
    images, labels = images.to(device), labels.to(device)
    
    with torch.no_grad():
        outputs = model(images[:num_images])
        predictions = outputs.argmax(dim=1)
        probabilities = F.softmax(outputs, dim=1)
    
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
    print("Network Weight Analysis")
    print("-" * 50)
    
    layer_names = []
    weight_means = []
    weight_stds = []
    
    for name, param in model.named_parameters():
        if 'weight' in name and param.dim() == 2:
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
    epochs = range(1, len(train_losses) + 1)
    
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 4))
    
    ax1.plot(epochs, train_losses, 'b-', label='Training Loss', linewidth=2)
    ax1.set_title('Training Loss (ANN)')
    ax1.set_xlabel('Epoch')
    ax1.set_ylabel('Loss')
    ax1.legend()
    ax1.grid(True, alpha=0.3)
    
    ax2.plot(epochs, train_accuracies, 'b-', label='Training Accuracy', linewidth=2)
    ax2.plot(epochs, test_accuracies, 'r-', label='Test Accuracy', linewidth=2)
    ax2.set_title('Model Accuracy (ANN)')
    ax2.set_xlabel('Epoch')
    ax2.set_ylabel('Accuracy (%)')
    ax2.legend()
    ax2.grid(True, alpha=0.3)
    
    plt.tight_layout()
    plt.show()

def compare_model_complexities():
    print("Comparing ANN Model Complexities")
    print("-" * 60)
    
    models = {
        'Standard ANN': MNISTNet_ANN(),
        'Wide ANN': MNISTNet_ANN(hidden_size=512)
    }
    
    for name, model in models.items():
        total_params = sum(p.numel() for p in model.parameters())
        trainable_params = sum(p.numel() for p in model.parameters() if p.requires_grad)
        
        print(f"{name}:")
        print(f"  Total parameters: {total_params:,}")
        print(f"  Trainable parameters: {trainable_params:,}")
        print(f"  Model size (MB): {total_params * 4 / 1024 / 1024:.2f}")
        print()

def save_model(model, filepath='mnist_ann_model.pth'):
    torch.save({
        'model_state_dict': model.state_dict(),
        'model_type': type(model).__name__,
        'input_size': 784,
        'num_classes': 10
    }, filepath)
    print(f'ANN model saved to {filepath}')

def load_model(filepath='mnist_ann_model.pth'):
    checkpoint = torch.load(filepath, map_location=device)
    
    model = MNISTNet_ANN().to(device)
    model.load_state_dict(checkpoint['model_state_dict'])
    model.eval()
    print(f'ANN model loaded from {filepath}')
    return model

def main():
    print("=== MNIST Handwritten Digit Classification with ANN ===")
    print("=== ANN을 사용한 MNIST 손글씨 숫자 분류 ===\n")
    
    print("Preparing data...")
    train_loader, test_loader = prepare_data()
    print(f"Training samples: {len(train_loader.dataset)}")
    print(f"Test samples: {len(test_loader.dataset)}\n")
    
    compare_model_complexities()
    
    print("Creating ANN model...")
    model = MNISTNet_ANN().to(device)
    
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
    
    print(f"\nANN training completed! Final accuracy: {final_accuracy:.2f}%")
    print("ANN 훈련 완료! 최종 정확도:", f"{final_accuracy:.2f}%")

if __name__ == "__main__":
    main()
