# Multiple Dimension Input  

## 回归数据集  

| x(hours) | y(points) |  
| --- | --- | 
| 1 | 2 |
| 2 | 4 |
| 3 | 6 | 
| 4 | ? |  



## 分类数据集  

| x(hours) | y(pass/fail) |
| --- | --- |
| 1 | 0(fail) |
| 2 | 0(fail) | 
| 3 | 1(pass) |
| 4 | ? |  


## Logistic Regression Model  

$$ \hat{y}^{(i)} = \sigma{(\sum_{n = 1}^{N} x_n^{(i)} \codt w_n + b)} $$  

## Mini-Batch  

$$ 
    \begin{bmatrix}  
    \hat{y}^{(1)} \\\
    \vdots \\\
    \hat{y}^{(N)}
    \end{bmatrix} = 
    \begin{bmatrix}
    \sigma{(z^{(1)})} \\\
    \vdots \\\
    \sigma{(z^{(N)})}
    \end{bmatrix} = \sigma{(
    \begin{bmatrix}
    z^{(1)} \\\
    \vdots \\\
    z^{(N)}
    \end{matrix})}
$$
