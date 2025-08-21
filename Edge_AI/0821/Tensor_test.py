import torch
# PyTorch 텐서의 차원(스칼라/벡터/행렬/3D 텐서)과 shape, dim()을 실습

# Scalar (0D tensor)
scalar = torch.tensor(5)
print("Scalar : ", scalar)
print("Shape : ", scalar.shape)
print("Dimensions : ", scalar.dim())
print("\n")

# Vecotr (1D tensor)
vector = torch.tensor([1, 2, 3, 4])
print("Vector : ", vector)
print("Shape : ", vector.shape)
print("Dimensions : ", vector.dim())
print("\n")

# Matrix (2D tensor)
matrix = torch.tensor([[1, 2], [3, 4], [5, 6]])
print("Matrix : ", matrix)
print("Shape : ", matrix.shape)
print("Dimensions : ", matrix.dim())
print("\n")

# Tensor (3D tensor)
tensor_3d = torch.tensor([[[1, 2], [3, 4]], [[5, 6], [7, 8]]])
print("3D tensor : ", tensor_3d)
print("Shape : ", tensor_3d.shape)
print("Dimensions : ", tensor_3d.dim())