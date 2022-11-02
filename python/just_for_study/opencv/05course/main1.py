import numpy as np
import matplotlib.pyplot as plt
import cv2 as cv

img = cv.imread('/home/zack/图片/wallPaper/wallhaven-m99ypk.jpg')
cv.namedWindow('img', cv.WINDOW_NORMAL)
cv.resizeWindow('img', 640, 480)

gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)

thresh, img_banary = cv.threshold(gray, 150, 255, cv.THRESH_BINARY)

contour, hierarchy = cv.findContours(img_banary, cv.RETR_TREE, cv.CHAIN_APPROX_SIMPLE)

img_copy = img
cv.drawContours(img_copy, contour, -1, (0, 255, 0), 2)

area = cv.contourArea(contour[1])
length = cv.arcLength(contour[1], closed=True)
print(area, length)

approx = cv.approxPolyDP(contour[1], 20, True)
print(type(approx))
cv.drawContours(img_copy, [approx], -1, (0, 255, 0), 2)

cv.imshow('img', np.hstack((img, img_copy)))

key = cv.waitKey(0)
if key == ord('q'):
    cv.destroyAllWindows()