import numpy as np
import matplotlib.pyplot as plt
import cv2 as cv

img = cv.imread('/home/zack/图片/wallPaper/wallhaven-v95eml.jpg')

cv.namedWindow('img', cv.WINDOW_NORMAL)
cv.resizeWindow('img', 640, 480)

# dx = cv.Sobel(img, cv.CV_64F, dx = 1, dy = 0, ksize=3)
# dy = cv.Sobel(img, cv.CV_64F, dx = 0, dy = 1, ksize=3)

# dx = cv.Scharr(img, cv.CV_64F, dx = 1, dy = 0)
# dy = cv.Scharr(img, cv.CV_64F, dx = 0, dy = 1)
#
# new_img = cv.add(dx, dy)
# new_img = cv.Laplacian(img, -1, ksize=3)

# lena1 = cv.Canny(img, 100, 200)
# lena2 = cv.Canny(img, 64, 128)

img = cv.cvtColor(img, cv.COLOR_BGR2GRAY)
new_img = cv.adaptiveThreshold(img, 255, cv.ADAPTIVE_THRESH_GAUSSIAN_C, cv.THRESH_BINARY, 11, 0)
cv.imshow('img', new_img)

key = cv.waitKey(0)
if key == ord('q'):
    cv.destroyAllWindows()