import cv2 as cv
import numpy as np
import matplotlib.pyplot as plt

img = np.zeros((512, 512, 3), np.uint8)

cv.line(img, (0, 0), (511, 511), (255, 0, 0), 5)
cv.rectangle(img, (384, 0), (510, 128), (0, 255, 0), 3)
cv.circle(img, (447, 63), 63, (0, 0, 255), -1)
font = cv.FONT_HERSHEY_SIMPLEX
cv.putText(img, "OpenCv", (10, 500), font, 4, (255, 255, 255), cv.LINE_AA)

plt.imshow(img[:, :, ::-1])
plt.title("匹配结果")
plt.xticks([]), plt.yticks([])
plt.show()

