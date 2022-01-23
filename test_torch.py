import torch.nn.functional as F
import torch

input = torch.randn(3, 5, requires_grad=True)
target = torch.randint(5, (3,), dtype=torch.int64)
print(input)
print(target)
loss = F.cross_entropy(input, target)
print(loss)
loss.backward()