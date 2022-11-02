import torch
import numpy as np

xy = np.loadtxt('diabetes.csv.gz', delimiter = ',', dtype = np.float32)
# np.loadtxt可以自动解压压缩包
# 第一个参数是包名
# 第二个参数是分割符
# 第三个参数是类型
x_data = torch.from_numpy(xy[:, : -1])  #拿出x
y_data = torch.from_numpy(xy[:, [-1]])  #拿出y

class Model(torch.nn.Module):
    def __init__(self):
        super(Model, self).__init__()
        self.linear1 = torch.nn.Linear(8, 6)
        self.linear2 = torch.nn.Linear(6, 4)
        self.linear3 = torch.nn.Linear(4, 1)
        self.sigmoid = torch.sigmoid()

    def forward(self, x):
        x = self.sigmoid(self.linear1(x))
        x = self.sigmoid(self.linear2(x))
        x = self.sigmoid(self.linear3(x))
        return x

    model = Model()

    critersion = torch.nn.BCELoss(reduction = 'sum')
    optimizer = torch.optim.SGD(model.parameters(), lr = 0.01)

    for epoch in range(100) :
        y_pred = model(x_data)
        loss = critersion(y_pred, y_data)
        print(epoch, loss.item())

        optimizer.zero_grad()
        loss.backward()

        optimizer.step()


