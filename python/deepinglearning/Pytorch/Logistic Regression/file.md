# Logistic Regression  

---  

## MNIST Dataset  

```Python
import torchvision
train_set = torchvision.datasets.MNIST(root = "../dataset/mnist", train = True, download = True)
test_set = torchvision.datasets.MNIST(root = "../datasets/mnist", train = False, download = True)
# 第一个参数是数据集的相对路径(也可以使用绝对路径)
# 第二个参数是是否是训练集，如果是True就是训练集，如果是False就是训练集
# 第三个参数是是否需要联网下载，如果当前没有则会自动下载
```

## CIFAR-10  

```Python
import torchvision
train_set = torchvision.datasets.CIFAR10(...)
test_set = torchvision.datasets.CIFAR10(...)
# 参数和MNIST一样
# 其中下载的数据集包含airplane、automobile、bird、cat、deer、dog、frog、horse、ship、truck这10种
```

## Logistic Function

$$ \sigma{(x)} = \frac{1}{1 + e^{-x}} $$  

- 这是激活函数，sigmoid()

### 其他的sigmoid函数

- $ erf (\frac{\sqrt{\pi}}{2}x) $
- $ \frac{x}{\sqrt{1 + x^2}} $
- $ tanh(x) $
- $ \frac{2}{\pi}arctan(\frac{\pi}{2}x) $
- $ \frac{2}{\pi}gd(\frac{\pi}{2}x) $
- $ \frac{x}{1 + \|x\|} $  

## Logistic Regression Model

$$ \hat{y} = \sigma{(w^Tx + b)} $$  

## Loss Function

$$ loss = -(y\log{\hat{y}} + (1 - y)\log{(1 - \hat{y})}) $$  
> ==比较的是，两个分布之间的差异==  

## Cost Function

$$ const = -\frac{1}{N} \sum_{n = 1}^{N}(y_n\log{\hat{y}_n} + (1 - y_n)\log{(1 - \hat{y}_n)}) $$  

