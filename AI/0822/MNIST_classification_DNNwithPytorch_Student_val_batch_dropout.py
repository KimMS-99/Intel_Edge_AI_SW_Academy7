import torch
import torch.nn as nn
import torch.optim as optim
import torch.nn.functional as F
from torch.utils.data import DataLoader, random_split
import torchvision
import torchvision.transforms as transforms
import matplotlib.pyplot as plt
import numpy as np
import os

device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
print(f'Using device: {device}')

class MNISTNet_DNN(nn.Module):
    def __init__(self, input_size=784, hidden_sizes=[1024, 512, 256, 128], num_classes=10):
        super(MNISTNet_DNN, self).__init__()
        
        self.fc1 = nn.Linear(input_size, hidden_sizes[0])
        self.bn1 = nn.BatchNorm1d(hidden_sizes[0])

        self.fc2 = nn.Linear(hidden_sizes[0], hidden_sizes[1])
        self.bn2 = nn.BatchNorm1d(hidden_sizes[1])

        self.fc3 = nn.Linear(hidden_sizes[1], hidden_sizes[2])
        self.bn3 = nn.BatchNorm1d(hidden_sizes[2])

        self.fc4 = nn.Linear(hidden_sizes[2], hidden_sizes[3])
        self.fc5 = nn.Linear(hidden_sizes[3], num_classes)

        self.dropout1 = nn.Dropout(0.3)
        self.dropout2 = nn.Dropout(0.4)
        self.dropout3 = nn.Dropout(0.5)
        
        self._initialize_weights()
    
    def _initialize_weights(self):
        for module in self.modules():
            if isinstance(module, nn.Linear):
                '''
                Select Method for initiate weight value
                '''
                nn.init.constant_(module.bias, 0)
                # nn.init_uniform_(module.weight)
                nn.init.normal_(module.weight, mean=0, std=1.0)
                # nn.init.normal_(module.weight, mean=0, std=0.05)

                # Xavier Uniform Distribution
                nn.init.xavier_uniform_(module.weight) 
                # Samples from: Uniform(-limit, +limit) where limit = sqrt(6 / (fan_in + fan_out))

                # Xavier Normal Distribution
                nn.init.xavier_normal_(module.weight)
                # Samples from: Normal(0, std) where std = sqrt(2 / (fan_in + fan_out))

    
    def forward(self, x):
        x = x.view(x.size(0), -1)
        
        x = self.fc1(x)
        x = self.bn1(x)
        x = F.relu(x)
        x = self.dropout1(x)
        
        x = self.fc2(x)
        x = self.bn2(x)
        x = F.relu(x)
        x = self.dropout2(x)
        
        x = self.fc3(x)
        x = self.bn3(x)
        x = F.relu(x)
        x = self.dropout3(x)
        
        x = self.fc4(x)
        x = F.relu(x)
        
        x = self.fc5(x)
        
        return x

def prepare_data():
    transform = transforms.Compose([
        transforms.ToTensor(),
        transforms.Normalize((0.1307,), (0.3081,))
    ])
    
    # full_train_dataset = torchvision.datasets.MNIST(
    full_train_dataset = torchvision.datasets.FashionMNIST(
        root='./data', 
        train=True, 
        download=True, 
        transform=transform
    )
    
    train_size = 50000
    val_size = 10000
    train_dataset, val_dataset = random_split(
        full_train_dataset, 
        [train_size, val_size],
        generator=torch.Generator().manual_seed(42)
    )
    
    # test_dataset = torchvision.datasets.MNIST(
    test_dataset = torchvision.datasets.FashionMNIST(
        root='./data', 
        train=False, 
        download=True, 
        transform=transform
    )
    
    train_loader = DataLoader(
        train_dataset, 
        batch_size=128, 
        shuffle=True,
        num_workers=2
    )
    
    val_loader = DataLoader(
        val_dataset,
        batch_size=1000,
        shuffle=False,
        num_workers=2
    )
    
    test_loader = DataLoader(
        test_dataset, 
        batch_size=1000, 
        shuffle=False,
        num_workers=2
    )
    
    return train_loader, val_loader, test_loader

def evaluate_model(model, data_loader, criterion):
    model.eval()
    total_loss = 0
    correct = 0
    total = 0
    
    with torch.no_grad():
        for data, target in data_loader:
            data, target = data.to(device), target.to(device)
            output = model(data)
            total_loss += criterion(output, target).item() * data.size(0)
            pred = output.argmax(dim=1, keepdim=True)
            correct += pred.eq(target.view_as(pred)).sum().item()
            total += target.size(0)
    
    avg_loss = total_loss / total
    accuracy = 100. * correct / total
    
    return avg_loss, accuracy

def train_model(model, train_loader, val_loader, test_loader, num_epochs=15):
    criterion = nn.CrossEntropyLoss()
    # optimizer = optim.SGD(model.parameters(), lr=0.01) # 1
    # optimizer = optim.SGD(model.parameters(), lr=0.01, momentum=0.9, weight_decay=1e-4) # 2
    # optimizer = optim.RMSprop(model.parameters(), lr=0.01, weight_decay=1e-4) # 3 
    optimizer = optim.Adam(model.parameters(), lr=0.001, weight_decay=1e-4) # 4
    scheduler = optim.lr_scheduler.StepLR(optimizer, step_size = 5, gamma = 0.5)

    scheduler.step() # Each Epoch
    print(f'    Learning Rate: {scheduler.get_last_lr()[0]:.6f}')

    train_losses = []
    train_accuracies = []
    val_losses = []
    val_accuracies = []
    test_accuracies = []
    
    best_val_accuracy = 0
    best_model_state = None
    
    print("Starting DNN training...")
    print("-" * 60)
    
    for epoch in range(num_epochs):
        model.train()
        running_loss = 0.0
        correct = 0
        total = 0
        
        for batch_idx, (data, target) in enumerate(train_loader):
            data, target = data.to(device), target.to(device)
            
            optimizer.zero_grad()
            
            output = model(data)
            loss = criterion(output, target)
            
            loss.backward()
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
        
        val_loss, val_accuracy = evaluate_model(model, val_loader, criterion)
        val_losses.append(val_loss)
        val_accuracies.append(val_accuracy)
        
        test_loss, test_accuracy = evaluate_model(model, test_loader, criterion)
        test_accuracies.append(test_accuracy)
        
        if val_accuracy > best_val_accuracy:
            best_val_accuracy = val_accuracy
            best_model_state = model.state_dict().copy()
        
        print(f'Epoch [{epoch+1}/{num_epochs}] Summary:')
        print(f'  Train Loss: {epoch_loss:.4f}, Train Acc: {epoch_accuracy:.2f}%')
        print(f'  Val Loss: {val_loss:.4f}, Val Acc: {val_accuracy:.2f}%')
        print(f'  Test Acc: {test_accuracy:.2f}%')
        print(f'  Best Val Acc: {best_val_accuracy:.2f}%')
        print("-" * 60)
    
    if best_model_state is not None:
        model.load_state_dict(best_model_state)
    
    return train_losses, train_accuracies, val_losses, val_accuracies, test_accuracies

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

def plot_training_history(train_losses, train_accuracies, val_losses, val_accuracies, test_accuracies):
    epochs = range(1, len(train_losses) + 1)
    
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 4))
    
    ax1.plot(epochs, train_losses, 'b-', label='Training Loss', linewidth=2)
    ax1.plot(epochs, val_losses, 'g-', label='Validation Loss', linewidth=2)
    ax1.set_title('Loss Curves (DNN)')
    ax1.set_xlabel('Epoch')
    ax1.set_ylabel('Loss')
    ax1.legend()
    ax1.grid(True, alpha=0.3)
    
    ax2.plot(epochs, train_accuracies, 'b-', label='Training Accuracy', linewidth=2)
    ax2.plot(epochs, val_accuracies, 'g-', label='Validation Accuracy', linewidth=2)
    ax2.plot(epochs, test_accuracies, 'r-', label='Test Accuracy', linewidth=2)
    ax2.set_title('Model Accuracy (DNN)')
    ax2.set_xlabel('Epoch')
    ax2.set_ylabel('Accuracy (%)')
    ax2.legend()
    ax2.grid(True, alpha=0.3)
    
    plt.tight_layout()
    plt.show()

def save_model(model, filename='mnist_dnn_model.pth'):
    # Save to current directory
    current_dir = os.getcwd()
    filepath = os.path.join(current_dir, filename)
    
    torch.save({
        'model_state_dict': model.state_dict(),
        'model_type': type(model).__name__,
        'input_size': 784,
        'num_classes': 10
    }, filepath)
    print(f'DNN model saved to {filepath}')

def load_model(filename='mnist_dnn_model.pth'):
    # Load from current directory
    current_dir = os.getcwd()
    filepath = os.path.join(current_dir, filename)
    
    checkpoint = torch.load(filepath, map_location=device)
    
    model = MNISTNet_DNN().to(device)
    model.load_state_dict(checkpoint['model_state_dict'])
    model.eval()
    print(f'DNN model loaded from {filepath}')
    return model

def main():
    print("=== MNIST Handwritten Digit Classification with DNN ===")
    print("=== DNN을 사용한 MNIST 손글씨 숫자 분류 ===\n")
    
    print("Preparing data...")
    train_loader, val_loader, test_loader = prepare_data()
    print(f"Training samples: {len(train_loader.dataset)}")
    print(f"Validation samples: {len(val_loader.dataset)}")
    print(f"Test samples: {len(test_loader.dataset)}\n")
    
    print("Creating DNN model...")
    model = MNISTNet_DNN().to(device)
    
    print("Model Architecture:")
    print(model)
    
    total_params = sum(p.numel() for p in model.parameters())
    trainable_params = sum(p.numel() for p in model.parameters() if p.requires_grad)
    print(f"\nTotal parameters: {total_params:,}")
    print(f"Trainable parameters: {trainable_params:,}")
    print(f"Model size: {total_params * 4 / 1024 / 1024:.2f} MB\n")
    
    train_losses, train_accs, val_losses, val_accs, test_accs = train_model(
        model, train_loader, val_loader, test_loader, num_epochs=15
    )
    
    print("\n=== Final Results ===")
    criterion = nn.CrossEntropyLoss()
    val_loss, val_accuracy = evaluate_model(model, val_loader, criterion)
    test_loss, test_accuracy = evaluate_model(model, test_loader, criterion)
    
    print(f"Final Validation Accuracy: {val_accuracy:.2f}%")
    print(f"Final Test Accuracy: {test_accuracy:.2f}%")
    
    analyze_network_weights(model)
    
    plot_training_history(train_losses, train_accs, val_losses, val_accs, test_accs)
    
    visualize_predictions(model, test_loader)
    
    save_model(model)
    
    print(f"\nDNN training completed!")
    print(f"Final validation accuracy: {val_accuracy:.2f}%")
    print(f"Final test accuracy: {test_accuracy:.2f}%")

if __name__ == "__main__":
    main()