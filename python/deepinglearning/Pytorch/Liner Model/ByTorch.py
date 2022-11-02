import torch

x_data = [1.0, 2.0, 3.0]    # x数据集
y_data = [2.0, 4.0, 6.0]    # y数据集

w = torch.Tensor([1.0])     # 权重的初始化，w的值只有一个，为1.0
w.requires_grad = True      # 说明w是需要计算梯度的

def foreward(x) :
    '''
    :param
        y_hat = w * x
        x: 给的训练样本
    :return:
        w * x: 前导算法推出y_hat
    '''
    return w * x

def loss(x, y) :
    '''
    :param
        loss = (y_hat - y)^2
        x: 训练样本
        y: 真实值
        y_pred: 预测的y_hat
        loss: 单例的损失函数值
    :return:
        loss: 单例的损失函数值
    '''
    y_pred = foreward(x)
    loss = pow((y_pred - y), 2)
    return loss

print("predict (before training)", 4, foreward(4).item())

for epoch in range(100) :
    for x, y in zip(x_data, y_data) :
        loss_val = loss(x, y)   # 每一个样本的损失函数，此时的loss是一个张量，也就是计算图
        loss_val.backward() # 反向传播，求出链路上的所有梯度，并且自动存储在对应变量中
        print("\tgrad: ", x, y, w.grad.item())  # w.grad就是保存的梯度， grad得到的是一个tensor
        w.data = w.data - 0.01 * w.grad.data    # w.grad.data才是保存的值，使用item的目的是为了防止产生张量，使其一直是标量
        w.grad.data.zero_() #将权重的所有梯度清零，在每一次更新之后都需要清零
    print("progress: ", epoch, loss_val.item())
print("predict (after training)", 4, foreward(4).item())


