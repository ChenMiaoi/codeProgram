import matplotlib.pyplot as plt
import numpy as np


def sigmoid(x) :
    w = 1
    b = 1
    z = w * x + b
    sig = 1 / (1 + np.exp(-z))
    plt.plot(x, sig)
    plt.title("The sigmoid function data", fontsize = 16)
    plt.xlabel("x datas")
    plt.ylabel("sigmoid()")
    plt.grid()
    plt.axhline(y=0.5, ls = '--', c = 'red')
    plt.show()

def tanh(x) :
    w = 1
    b = 1
    z = w * x + b
    act = (np.exp(z) - np.exp(-z)) / (np.exp(z) + np.exp(-z))
    plt.plot(x, act)
    plt.title("The tanh function data", fontsize=16)
    plt.xlabel("x datas")
    plt.ylabel("tanh()")
    plt.grid()
    plt.axhline(y=0.0, ls='--', c='red')
    plt.savefig("tanh.png")
    plt.show()

def ReLU(x) :
    w = 1
    b = 0
    z = w * x + b
    act = np.maximum(z, 0)
    plt.plot(x, act)
    plt.title("The ReLU function data", fontsize=16)
    plt.xlabel("x datas")
    plt.ylabel("ReLU()")
    plt.grid()
    plt.axvline(x=0.0, ls='--', c='red')
    plt.axhline(y=0.0, ls='--', c='red')
    plt.savefig("ReLU.png")
    plt.show()

def lackReLU(x):
    w = 1
    b = 0
    z = w * x + b
    act = np.maximum(z, 0.01 * z)
    plt.plot(x, act)
    plt.title("The lackReLU function data", fontsize=16)
    plt.xlabel("x datas")
    plt.ylabel("lackReLU()")
    plt.grid()
    plt.axvline(x=0.0, ls='--', c='red')
    plt.axhline(y=0.0, ls='--', c='red')
    plt.savefig("lackReLU.png")
    plt.show()

if __name__ == "__main__" :
    print("sigmoid function")
    x_data = np.arange(-10.0, 10.0, 0.1)
    # sigmoid(x_data)
    # tanh(x_data)
    # ReLU(x_data)
    # lackReLU(x_data)