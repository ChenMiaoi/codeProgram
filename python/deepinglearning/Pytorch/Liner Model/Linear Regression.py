import torch

class LinearModel(torch.nn.Module) :
    '''
        torch.nn.Module是torch中神经网络的基类，包含了很多需要用到的
    '''
    def __init__(self):
        super(LinearModel, self).__init__()
        # 调用父类的构造，LinearModel是自定义的名称
        self.linear = torch.nn.Linear(1, 1)
        # torch.nn.Linear是torch中的一个类，在这里构造了一个匿名对象: y = wx + b
        # nn.Linear(in_features, out_features, bias = True)，第一个参数是输入维数，第二个参数是输出维度，要求输出输入维度相等
        # 里面包含了两个Tensors：weight和bias
        # 第三个参数是决定要不要偏置量

    # 重写了父类的forward
    def forward(self, x):
        y_pred = self.linear(x) # wx + b传入的x
        return y_pred

model = LinearModel()  # 注意，这个model是一个可调用的

criterion = torch.nn.MSELoss(reduction='sum')
# 损失函数，torch.nn.MSELoss(size_average = True, reduce  = True)
# 第一个参数 是确认是否求均值
# 第二个参数 是确定是否求和降维，但一般只考虑第一个参数
# 注意，在现在版本的MSELoss中，size_average = True用reduction = 'sum'代替

optimizer =torch.optim.SGD(model.parameters(), lr = 0.01)
# 优化器，torch.optim.SGD(params, lr = <object object>, momentum = 0, dampening = 0, weight_decay = 0, nesterov = False)
# 注意，这个是一个类
# 第一个参数是权重，model.parameters()会检查model中的所有成员权重，会调用linear.parameters
# 第二个参数是学习率，lr = learning rate
# 后面的参数暂时不考虑
'''
    另外的优化器：
    torch.optim.Adagrad
    torch.optim.Adam
    touch.optim.Adamax
    touch.optim.ASGD
    touch.optim.LBFGS
    touch.optim.RMSprop
    touch.optim.Rprop
    touch.optim.SGD
'''

x_data = torch.Tensor([[1.0], [2.0], [3.0]])
y_data = torch.Tensor([[2.0], [4.0], [6.0]])

for epoch in range(1100) :
    y_pred = model(x_data) #通过model算出y_hat
    loss = criterion(y_pred,  y_data)   # 算出损失函数
    print(epoch, loss)  # 打印的时候loss会自动调用__str__()，因此不会产生计算图

    optimizer.zero_grad()   # 在反向传播之前，一定要将梯度置零
    loss.backward() # 反向传播
    optimizer.step()    # step函数就是用来更新的，会自动调用预先设置的学习率
    print("w = ", model.linear.weight.item())   # linear中有内置的weight方法取出权重
    print("b = ", model.linear.bias.item()) # linear中有内置的bias方法取出偏置

x_test = torch.Tensor([[4.0]])
y_test = model(x_test)
print("y_pred = ", y_test.data)