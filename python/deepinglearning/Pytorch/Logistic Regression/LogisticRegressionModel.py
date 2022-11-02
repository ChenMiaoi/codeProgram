import matplotlib.pyplot as plt
import torch
import torch.nn.functional as F #这个functional模块中包含了我们需要的sigmoid函数

class LogisticRegressionModel(torch.nn.Module) :
    def __init__(self):
        super(LogisticRegressionModel, self).__init__()
        self.linear = torch.nn.Linear(1, 1)

    def forward(self, x):
        y_pred =  torch.sigmoid(self.linear(x)) # y_hat = sigmoid(z)， z = wx + b
        # 此处使用torch.sigmoid代替F.sigmoid
        return y_pred

model = LogisticRegressionModel()

critersion = torch.nn.BCELoss(reduction = 'sum')
# 二分类的交叉熵
optimizer = torch.optim.SGD(model.parameters(), lr = 0.01)

x_data = torch.Tensor([[1.0], [2.0], [3.0]])
y_data = torch.Tensor([[0.0], [0.0], [1.0]])

for epoch in range(1000) :
    y_pred = model(x_data)
    loss = critersion(y_pred, y_data)
    print(epoch, loss.item())

    optimizer.zero_grad()
    loss.backward()
    optimizer.step()

