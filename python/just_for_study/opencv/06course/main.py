import numpy as np
import matplotlib.pyplot as plt
import cv2 as cv

img = cv.imread('/home/zack/下载/QQ_Image_1658119341755.jpg')

# lap0 = img - cv.pyrUp(cv.pyrDown(img))
# lap1 = lap0 - cv.pyrUp(cv.pyrDown(lap0))
#
# cv.imshow('img', img)
# cv.imshow('lap0', lap0)
# cv.imshow('lap1', lap1)

# gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)
#
# plt.hist(gray.ravel(), bins=256, range=[0, 255])
# plt.show()

gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)

gray_dark = gray - 40
gray_bright = gray + 40

hist_gray = cv.calcHist([gray], [0], None, [256], [0, 255])
hist_dark = cv.calcHist([gray_dark], [0], None, [256], [0, 255])
hist_bright = cv.calcHist([gray_bright], [0], None, [256], [0, 255])

plt.plot(hist_gray)
plt.plot(hist_dark)
plt.plot(hist_bright)
plt.show()

dark_equ = cv.equalizeHist(gray_dark)
bright_equ = cv.equalizeHist(gray_bright)

cv.imshow('gray_dark', np.hstack((gray_dark, dark_equ)))
cv.imshow('gray_bright', np.hstack((gray_bright, bright_equ)))

key = cv.waitKey(0)
if key == ord('q'):
    cv.destroyAllWindows()