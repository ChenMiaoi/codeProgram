import torch
import matplotlib.pyplot as plt

x_data = [1.0, 2.0, 3.0]
y_data = [4.0, 8.0, 12.0]

w = torch.Tensor([1.0, 2.0])
b = torch.Tensor([1.0])
w.requires_grad = True
b.requires_grad = True

def foreward(x) :
    return w[0] * (x ** 2) + w[1] * x + b
print("predict (after training)", 4, foreward(4).item())
def loss(x, y) :
    y_pred = foreward(x)
    loss = pow((y_pred - y), 2)
    return loss

print("predict (before training)", 4, foreward(4).item())

for epoch in range(1000) :
    for x, y in zip(x_data, y_data) :
        loss_val = loss(x, y)
        loss_val.backward()
        print("\tgrad: ", x, y, w.grad.numpy(), b.grad.item())
        w.data = w.data - 0.01 * w.grad.data
        b.data = b.data - 0.01 * b.grad.data
        w.grad.data.zero_()
        b.grad.data.zero_()
    print("progress: ", epoch, loss_val.item())
print("predict (after training)", 4, foreward(4).item())