# Linear Model

---  

## The Example

- if here is a data model  

| x(hours) | y(points) |
| -------- |-----------|
| 1 | 2 |
| 2 | 4 | 
| 3 | 6 |
| 4 | ? |

- And the question is what would be  the grade if I study 4 hours?
  - we can input the 4 into the model of the data set, and using the data set to gain the 4 -- points
  - we call the 1 ~ 3 hours and the corresponding y as Training Set
  - we call the 4 which we want to input and the corresponding y as Test Set
  - **and the whole we can call the Supervised Learning**

## Linear Model

$$ \hat{y} = w * x + b $$  

- but we often use the estimated 

$$ \hat{y} = w * x $$

## Loss Function

$$ loss = (\hat{y} - y)^2 = (w * x - y)^2 $$  

## Cost Function(Mean Square Error -- MSE)  

$$ cost = \frac{1}{N}\sum_{n = 1}^{N}(\hat{y}_n - y_n)^2 $$  

