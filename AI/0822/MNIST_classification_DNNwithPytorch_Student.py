import torch
import torch.nn as nn
import torch.optim as optim
import torch.nn.functional as F
from torch.utils.data import DataLoader
from torch.utils.data import DataLoader, random_split
import torchvision
import torchvision.transforms as transforms
import matplotlib.pyplot as plt
import numpy as np
import os

# GPU가 있으면 CUDA, 없으면 CPU 사용
device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
print(f'Using device: {device}')

class MNISTNet_DNN(nn.Module):
    """ 784(28x28) 평탄화 입력을 받는 완전연결 DNN: 4개 은닉층 + 출력 10 """
    def __init__(self, input_size=784, hidden_sizes=[1024, 512, 256, 128], num_classes=10):
        super(MNISTNet_DNN, self).__init__()
        
        # 완전연결(Linear) 계층 정의
        self.fc1 = nn.Linear(input_size, hidden_sizes[0])
        self.fc2 = nn.Linear(hidden_sizes[0], hidden_sizes[1])
        self.fc3 = nn.Linear(hidden_sizes[1], hidden_sizes[2])
        self.fc4 = nn.Linear(hidden_sizes[2], hidden_sizes[3])
        self.fc5 = nn.Linear(hidden_sizes[3], num_classes)
        
        self._initialize_weights()
    
    def _initialize_weights(self):
        """ 가중치 초기화: Xavier Uniform, bias=0 """
        for module in self.modules():
            if isinstance(module, nn.Linear):
                nn.init.xavier_uniform_(module.weight)
                nn.init.constant_(module.bias, 0)
    
    def forward(self, x):
        # (N, 1, 28, 28) -> (N, 784)로 평탄화
        x = x.view(x.size(0), -1)
        
        # 은닉층 + ReLU
        x = self.fc1(x)
        x = F.relu(x)
        
        x = self.fc2(x)
        x = F.relu(x)
        
        x = self.fc3(x)
        x = F.relu(x)
        
        x = self.fc4(x)
        x = F.relu(x)
        
        # 마지막 층은 로짓 출력(Softmax 적용 안 함)
        x = self.fc5(x)
        
        return x

def prepare_data():
    """ FashionMNIST 데이터셋 로드 + 텐서화/정규화 + DataLoader 생성 """
    transform = transforms.Compose([
        transforms.ToTensor(),  # [0,1] 범위 텐서
        transforms.Normalize((0.1307,), (0.3081,)) # 평균/표준편차 정규화(관습적 값)
    ])
    
    # train_dataset = torchvision.datasets.MNIST(
    train_dataset = torchvision.datasets.FashionMNIST(
        root='./data', 
        train=True, 
        download=True, 
        transform=transform
    )

    # train_dataset = torchvision.datasets.MNIST(
    test_dataset = torchvision.datasets.FashionMNIST(
        root='./data', 
        train=False, 
        download=True, 
        transform=transform
    )
    
    # 미니배치/셔플/병렬 로딩 설정
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
    """ 학습 루프: 순전파→손실→역전파→옵티마이저 스텝, 에폭별 로그/평가 """
    criterion = nn.CrossEntropyLoss() # 다중분류용 손실(로짓 입력)
    optimizer = optim.SGD(model.parameters(), lr=0.01, momentum=0.9, weight_decay=1e-4)

    train_losses = []
    train_accuracies = []
    test_accuracies = []
    
    print("Starting DNN training...")
    print("-" * 60)
    
    for epoch in range(num_epochs):
        model.train() # 드롭아웃/BN 등을 훈련 모드로(여기선 FC만)
        running_loss = 0.0
        correct = 0
        total = 0
        
        for batch_idx, (data, target) in enumerate(train_loader):
            data, target = data.to(device), target.to(device)
            
            optimizer.zero_grad() # 누적된 기울기 초기화
            
            output = model(data) # 순전파
            loss = criterion(output, target) # 손실 계산
            
            loss.backward() # 역전파(기울기 계산)
            optimizer.step() # 가중치 갱신
            
            # 통계 집계
            running_loss += loss.item()
            pred = output.argmax(dim=1, keepdim=True)
            correct += pred.eq(target.view_as(pred)).sum().item()
            total += target.size(0)
            
            if batch_idx % 100 == 0:
                print(f'Epoch: {epoch+1}/{num_epochs}, Batch: {batch_idx}/{len(train_loader)}, '
                      f'Loss: {loss.item():.6f}, Accuracy: {100.*correct/total:.2f}%')
        
        # 에폭 요약
        epoch_loss = running_loss / len(train_loader)
        epoch_accuracy = 100. * correct / total
        train_losses.append(epoch_loss)
        train_accuracies.append(epoch_accuracy)
        
        # 에폭마다 테스트 정확도 측정
        test_accuracy = test_model(model, test_loader, verbose=False)
        test_accuracies.append(test_accuracy)
        
        print(f'Epoch [{epoch+1}/{num_epochs}] Summary:')
        print(f'  Train Loss: {epoch_loss:.4f}, Train Acc: {epoch_accuracy:.2f}%, Test Acc: {test_accuracy:.2f}%')
        print("-" * 60)
    
    return train_losses, train_accuracies, test_accuracies

def test_model(model, test_loader, verbose=True):
    """ 평가 루틴: 평균 손실과 전체 정확도 계산 """
    model.eval() # 평가 모드(드롭아웃/BN 고정)
    test_loss = 0
    correct = 0
    
    criterion = nn.CrossEntropyLoss(reduction='sum') # 배치 손실 합으로 누적
    
    with torch.no_grad(): # 그래디언트 비활성화(메모리/속도 이점)
        for data, target in test_loader:
            data, target = data.to(device), target.to(device)
            output = model(data)
            test_loss += criterion(output, target).item()
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
    """ 테스트 샘플 8개에 대해 정답/예측/신뢰도 시각화 """
    model.eval()
    
    data_iter = iter(test_loader)
    images, labels = next(data_iter)
    images, labels = images.to(device), labels.to(device)
    
    with torch.no_grad():
        outputs = model(images[:num_images])
        predictions = outputs.argmax(dim=1)
        probabilities = F.softmax(outputs, dim=1) # 각 클래스 확률
    
    fig, axes = plt.subplots(2, 4, figsize=(12, 6))
    axes = axes.ravel()
    
    for i in range(num_images):
        img = images[i].cpu().squeeze()
        true_label = labels[i].cpu().item()
        pred_label = predictions[i].cpu().item()
        confidence = probabilities[i][pred_label].cpu().item()
        
        axes[i].imshow(img, cmap='gray')
        color = 'green' if true_label == pred_label else 'red' # 정답 여부 색상
        axes[i].set_title(f'True: {true_label}, Pred: {pred_label}\nConf: {confidence:.3f}', 
                         color=color, fontsize=10)
        axes[i].axis('off')
    
    plt.tight_layout()
    plt.show()

def analyze_network_weights(model):
    """ 각 Linear 층 가중치의 통계(평균/표준편차/최소/최대)와 막대그래프 출력 """
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
            
            # 층별 통계 로그
            print(f"Layer: {name}")
            print(f"  Shape: {param.shape}")
            print(f"  Mean: {param.data.mean().item():.6f}")
            print(f"  Std: {param.data.std().item():.6f}")
            print(f"  Min: {param.data.min().item():.6f}")
            print(f"  Max: {param.data.max().item():.6f}")
            print()
    
    # 평균/표준편차 막대그래프
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
    """ 손실/정확도 학습 곡선 그리기 """
    epochs = range(1, len(train_losses) + 1)
    
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 4))
    
    ax1.plot(epochs, train_losses, 'b-', label='Training Loss', linewidth=2)
    ax1.set_title('Training Loss (DNN)')
    ax1.set_xlabel('Epoch')
    ax1.set_ylabel('Loss')
    ax1.legend()
    ax1.grid(True, alpha=0.3)
    
    ax2.plot(epochs, train_accuracies, 'b-', label='Training Accuracy', linewidth=2)
    ax2.plot(epochs, test_accuracies, 'r-', label='Test Accuracy', linewidth=2)
    ax2.set_title('Model Accuracy (DNN)')
    ax2.set_xlabel('Epoch')
    ax2.set_ylabel('Accuracy (%)')
    ax2.legend()
    ax2.grid(True, alpha=0.3)
    
    plt.tight_layout()
    plt.show()

def save_model(model, filename='mnist_dnn_model.pth'):
    """ 모델 가중치(state_dict)와 메타정보를 파일로 저장 """
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
    """ 저장된 체크포인트에서 동일 구조 모델로 로드 """
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
    """ 엔트리: 데이터 준비 → 모델 생성/요약 → 학습 → 평가/시각화 → 저장 """
    print("=== MNIST Handwritten Digit Classification with DNN ===")
    print("=== DNN을 사용한 MNIST 손글씨 숫자 분류 ===\n")
    
    print("Preparing data...")
    train_loader, test_loader = prepare_data()
    print(f"Training samples: {len(train_loader.dataset)}")
    print(f"Test samples: {len(test_loader.dataset)}\n")
    
    print("Creating DNN model...")
    model = MNISTNet_DNN().to(device)
    
    # 모델 요약 정보(파라미터 수/메모리 추정)
    print("Model Architecture:")
    print(model)
    total_params = sum(p.numel() for p in model.parameters())
    trainable_params = sum(p.numel() for p in model.parameters() if p.requires_grad)
    print(f"\nTotal parameters: {total_params:,}")
    print(f"Trainable parameters: {trainable_params:,}")
    print(f"Model size: {total_params * 4 / 1024 / 1024:.2f} MB\n") # float32 기준
    
    # 학습
    train_losses, train_accs, test_accs = train_model(model, train_loader, test_loader, num_epochs=15)
    
    print("\n=== Final Test Results ===")
    final_accuracy = test_model(model, test_loader)
    
    analyze_network_weights(model)
    plot_training_history(train_losses, train_accs, test_accs)
    visualize_predictions(model, test_loader)
    
    save_model(model)
    
    print(f"\nDNN training completed! Final accuracy: {final_accuracy:.2f}%")
    print("DNN 훈련 완료! 최종 정확도:", f"{final_accuracy:.2f}%")

if __name__ == "__main__":
    main()