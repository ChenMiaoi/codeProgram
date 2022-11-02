import numpy as np
import matplotlib.pyplot as plt
import h5py # 为了使用h5的数据集
from lr_utils import load_dataset 

train_set_x_orig, train_set_y, test_set_x_orig, test_set_y, classes = load_dataset()
'''
    train_set_x_orig    训练集x的图像数据
    train_set_y         训练集y的二分值 [0, 1]
    test_set_x_orig     测试集x的图像数据
    test_set_y          测试集y的二分值 [0, 1]
    classes             保存以bytes类型的两个字符串数据
'''
m_train = train_set_y.shape[1] # 训练集里面照片的数量
# 因为train_y.shape(1, m)
m_test = test_set_y.shape[1] # 测试集里面照片的数量
# 因为test_y.shape(1, m)
num_px = train_set_x_orig.shape[1] # 训练、测试集里面的图片的宽度和高度

print("训练集的数量: m_train = " + str(m_train))
print("测试集的数量: m_test  = " + str(m_test))
print("每张图片的宽/高 : num_px = " + str(num_px))
print("每张图片的大小: (" + str(num_px) + ", " + str(num_px) + ", 3)")
print("训练集_图片的维度: " + str(train_set_x_orig.shape))
print("训练集_标签的维度: " + str(train_set_y.shape))
print("测试集_图片的维度: " + str(test_set_x_orig.shape))
print("测试集_标签的维度: " + str(test_set_y.shape))

# 将训练集的维度降低并转置
train_set_x_flatten = train_set_x_orig.reshape(train_set_x_orig.shape[0], -1).T
# 将测试集的维度降低并转置
test_set_x_flatten = test_set_x_orig.reshape(test_set_x_orig.shape[0], -1).T
# 在reshape中-1就是让解释器去运算数组变成矩阵后有多少列。而ndarray.T就是转置

print("----------------------------------------------------------")
print("训练集降维最后的维度: " + str(train_set_x_flatten.shape))
print("训练集_标签的维度: " + str(train_set_y.shape))
print("测试集降维最后的维度: " + str(test_set_x_flatten.shape))
print("测试集_标签的维度: " + str(test_set_y.shape))

'''
    为了显示色彩，我们需要将矩阵的每一个数据集除以255
    因为色彩的表示是用RGB通道，像素值在区间[0, 255]因此，除以255能够让数据位于[0, 1]区间
'''
train_set_x = train_set_x_flatten / 255
test_set_x  = test_set_x_flatten / 255

# 到这里，数据的准备就完成了

def sigmoid(z) :
    """
    param :
        z -- 任何大小的标量或numpy数组
    
    return var :
        s -- sigmoid(z)
    """
    s = 1 / (1 + np.exp(-z))
    return s

def initialize_zeros(dim) :
    """
    此函数为dw创建一个维度为(dim, 1)的0向量，并将db初始化为0
    param :
        dim -- 我们想要的dw矢量大小
    
    return var :
        dw -- 维度为(dim, 1)的初始化向量
        db -- 初始化的标量(对应于偏差)
    """
    dw = np.zeros((dim, 1))
    db = 0
    
    assert(dw.shape == (dim, 1))
    assert(isinstance(db, float) or isinstance(db ,int))
    return (dw, db)

def propagate(w, b, X, Y) :
    """
    实现前向和后向传播的成本函数以及梯度下降
    param :
        w -- 权重，大小不等的数组(num_px * num_px * 3, 1)
        b -- 偏差，一个标量
        X -- 矩阵类型为(num_px * num_px * 3, m)
        Y -- 真正的"标签"矢量，矩阵维度为(1, m)
    
    return var :
        cost -- Logistic Regression cost function
        dw   -- 相对于w的损失梯度，因此与w相同的形状
        db   -- 相对于b的损失梯度，因此与b相同的形状
    """
    m = X.shape[1]
    
    # 正向传播
    A = sigmoid(np.dot(w.T, X) + b)     # 计算激活函数值
    cost = (- 1 / m) * np.sum(Y * np.log(A) + (1 - Y) * np.log(1 - A))  # 计算成本函数
    
    # 反向传播
    dw = (1 / m) * np.dot(X, (A - Y).T)
    db = (1 / m) * np.sum(A - Y)
    
    # 判断数据
    assert(dw.shape == w.shape)
    assert(db.dtype == float)
    cost = np.squeeze(cost)
    assert(cost.shape == ())
    
    # 创建字典，保存dw，db
    grads = {
        "dw" : dw, 
        "db" : db
    }
    return (grads, cost)

def optimize(w, b, X, Y, num_iterations, learning_rate, print_cost = False) :
    """
    此函数通过运行梯度下降算法来优化w和b
    param :
        w -- 权重，大小不等的数组(num_px * num_px * 3, 1)
        b -- 偏差，一个标量
        X -- 维度为(num_px * num_px * 3, m)
        Y -- 真正的"标签"矢量，矩阵维度为(1, m)
        num_iterations -- 优化循环的迭代次数
        learning_rate  -- 梯度下降更新规则的学习率
        print_cost     -- 每一百步打印一次损失值
        
    return var :
        params -- 包含权重w和偏差b的字典
        grads  -- 包含权重和偏差相对于成本函数梯度下降的字典
        成本   -- 优化期间计算的所有成本列表，将用于绘制学习曲线
        
    tips :
    我们需要写下两步并遍历 :
        1) 计算当前参数的成本和剃度下降，使用propagate()
        2) 使用w和b的梯度下降更新参数
    """
    
    costs = []
    
    for i in range(num_iterations) :
        grads, cost = propagate(w, b, X, Y)
        dw = grads["dw"]
        db = grads["db"]
        
        w = w - learning_rate * dw
        b = b - learning_rate * db
        
        # 记录成本
        if i % 100 == 0 :
            costs.append(cost)
        # 打印成本数据 -- 100步打印一次
        if (print_cost) and (i % 100 == 0) :
            print("迭代的次数: %i,  误差值: %f"% (i, cost))
    
    params = {
        "w" : w,
        "b" : b
    }
    grads  = {
        "dw" : dw,
        "db" : db
    }
    return (params, grads, costs)

def predict (w, b, X) :
    """
    使用学习逻辑回归参数logistic(w, b) 预测标签是0还是1
    param :
        w -- 权重，大小不等的数组(num_px * num_px * 3, 1)
        b -- 偏差，一个标量
        X -- 维度为(num_px * num_px * 3, m)
        
    return var :
        Y_prediction -- 包含X中所有图片的预测值的一个numpy数组
    """
    
    m = X.shape[1] # 图片的数量
    Y_prediction = np.zeros((1, m))
    w = w.reshape(X.shape[0], 1)
    
    # 计算预测猫在图片中出现的概率
    A = sigmoid(np.dot(w.T, X) + b)
    for i in range(A.shape[1]) :
        # 将概率a[0, i]转换为实际预测p[0, i]
        Y_prediction[0, i] = 1 if A[0, i] > 0.5 else 0
        # 如果实际概率大于0.5就认为是猫
    
    # 判断数据
    assert (Y_prediction.shape == (1, m))
    
    return Y_prediction

def model(X_train, Y_train, X_test, Y_test, num_iterations = 2000, learning_rate = 0.5, print_cost = False) :
    """
    通过调用之前实现的函数来构建逻辑回归模型
    param :
        X_train -- numpy的数组，维度为(num_px * num_px * 3, m_train)的训练集
        Y_train -- numpy的数组，维度为(1, m_train)(矢量)的训练标签集
        X_test  -- numpy的数组，维度为(num_px * num_px * 3, m_train)的测试集
        Y_test  -- numpy的数组，维度为(1, m_test)(向量)的测试标签集
        num_iterations -- 表示用于优化的迭代次数的超参数
        learning_rate  -- 表示optimize() 更新规则中使用的学习速率的超参数
        print_cost     -- 设置为True以100为频率迭代打印成本
        
    return var :
        d -- 包含有关模型信息的字典
    """
    
    w, b = initialize_zeros(X_train.shape[0])
    
    parameters, grads, costs = optimize(w, b, X_train, Y_train, num_iterations, learning_rate, print_cost)
    
    # 从字典参数中检索参数w和b
    w, b = parameters["w"], parameters["b"]
    
    # 预测测试/训练集的例子
    Y_prediction_test  = predict(w, b, X_test)
    Y_prediction_train = predict(w, b, X_train)
    
    # 打印训练后的准确性
    print("训练集准确性: ", format(100 - np.mean(np.abs(Y_prediction_train - Y_train)) * 100), "%")
    print("测试集准确性: ", format(100 - np.mean(np.abs(Y_prediction_test - Y_test)) * 100), "%")
    
    d = {
        "costs" : costs,
        "Y_prediction_test" : Y_prediction_test,
        "Y_prediction_train" : Y_prediction_train,
        "w" : w,
        "b" : b,
        "learning_rate" : learning_rate,
        "num_iterations" : num_iterations
    }
    return d

d = model(train_set_x, train_set_y, test_set_x, test_set_y, num_iterations = 2000, learning_rate = 0.005, print_cost = True)

# 绘制图像
costs = np.squeeze(d["costs"])
plt.plot(costs)
plt.ylabel("cost", size= 14)
plt.xlabel("iterations (per hundreds)", size = 14)
plt.title("Learning rate = " + str(d["learning_rate"]), fontsize = 20)
plt.savefig("Learning Rate.jpg")
plt.show()