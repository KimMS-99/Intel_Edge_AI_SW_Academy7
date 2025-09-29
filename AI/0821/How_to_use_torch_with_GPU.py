import torch

# GPU setup
device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')

# GPU Information
if torch.cuda.is_available():
    print(f"GPU 사용가능 : {torch.cuda.get_device_name(0)}")
    print(f"현재 선택된 디바이스 : {device}")

# # Model and data to GPU/CPU
# model = model.to(device)
# data, target = data.to(device), target.to(device)

# # Training loop
# output = model(data) # Both on same device