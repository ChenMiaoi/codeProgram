import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d.axes3d import Axes3D

x_data = [1.0, 2.0, 3.0]
y_data = [2.0, 4.0, 6.0]

def forward(x) :
    '''
    :param
        x: for the x
        w: for the weight
    :return:
        w * x: is the y_hat
    '''
    return w * x + b

def loss(x, y) :
    '''
    :param
        x: for the x
        y: for the real y
        y_pred: for the prediction y
    :return:
        loss: the loss function
    '''
    y_pred = forward(x)
    loss = pow((y_pred - y), 2)
    return loss

w_list = []
mse_list = []
b_list = []

for w in np.arange(0.0, 4.1, 0.1) :
    b = np.random.random() % 3 + 1
    print('w = {0}, b = {1}'.format(w, b))
    cost = 0
    for x_val, y_val in zip(x_data, y_data) :
        y_pred_val = forward(x_val)
        loss_val = loss(x_val, y_val)
        cost += loss_val
        print('\t', x_val, y_val, y_pred_val, loss_val)
    print('MSE = ', cost / 3)
    w_list.append(w)
    b_list.append(b)
    mse_list.append(cost / 3)

fig = plt.figure()
ax3 = plt.axes(projection = '3d')
X, Z = np.meshgrid(w_list, b_list)
Y = mse_list * X + Z

ax3.plot_surface(X, Y, Z,cmap='rainbow')

plt.show()