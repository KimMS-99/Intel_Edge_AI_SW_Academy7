import torch
import torch.nn as nn
import torch.nn.functional as F
from torchviz import make_dot

torch.manual_seed(42)

# 1. Model Definition
model = nn.Linear(5, 3)

# 2. Data (One-hot encoded target)
x = torch.ones(5)
y = torch.tensor([0., 0., 1.])  # One-hot encoding for class 3

# 3. Forward Pass
output = model(x)
loss = F.binary_cross_entropy_with_logits(output, y)

# 4. Backward Pass
loss.backward()

# 5. Individual Gradient Values
weight_gradients = model.weight.grad  # Shape: (3, 5) - all individual ∂L/∂w_i
bias_gradients   = model.bias.grad    # Shape: (3,)   - all individual ∂L/∂b_i

# 6. Visualization
dot = make_dot(loss, params=dict(model.named_parameters()))
dot.render('computational_graph', format='png')
dot.view()
