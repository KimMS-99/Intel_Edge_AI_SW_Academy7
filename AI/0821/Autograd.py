import torch
import torch.nn as nn

fc1 = nn.Linear(3, 1)

print("Weight requires_grad : ", fc1.weight.requires_grad)
print("Bias requires_grad : ", fc1.bias.requires_grad)