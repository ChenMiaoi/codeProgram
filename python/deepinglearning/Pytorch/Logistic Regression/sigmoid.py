import numpy as np
import matplotlib.pyplot as plt

x_data = np.arange(-10.0, 10.0, 0.1)
y_data = 1 / (1 + np.exp(-x_data))

plt.plot(x_data, y_data)
plt.grid()
plt.show()
