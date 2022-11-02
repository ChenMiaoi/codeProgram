import numpy as np
import matplotlib.pyplot as plt

x_data = [1.0, 2.0, 3.0]
y_data = [2.0, 4.0, 6.0]

w = 1.0

def forward(x) :
    return w * x

def cost(xs, ys) :
    cost = 0
    for x, y in zip(xs, ys) :
        y_pred = forward(x)
        cost += pow((y_pred - y), 2)
    return cost / len(xs)   # cost

def gradient(xs, ys) :
    grad = 0
    for x, y in zip(xs, ys) :
        grad += 2 * x * (w * x - y)     # dw
    return grad / len(xs)

print("Predict (before training)", 4, forward(4))

Epoch_list = []
cost_list = []
for epoch in range(100) :
    cost_val = cost(x_data, y_data)
    grad_val = gradient(x_data, y_data) # dw
    w -= 0.01 * grad_val
    print("Epoch: ", epoch, "w = ", w, "loss = ", cost_val)
    Epoch_list.append(epoch)
    cost_list.append(cost_val)
print("Predict (after training)", 4, forward(4))

plt.plot(Epoch_list, cost_list)
plt.title("Gradient Descent", fontsize = 16)
plt.xlabel("Epoch", size = 14)
plt.ylabel("Cost", size = 14)

plt.show()