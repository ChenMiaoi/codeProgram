import cv2
import matplotlib.pyplot as plt

img = cv2.imread("img1.png", cv2.IMREAD_GRAYSCALE)
cv2.imshow("img", img)
cv2.waitKey()

#plt.imshow(img)
#plt.show()
cv2.imwrite("GRAYSCALE.png", img)