import cv2 as cv
import numpy as np
import matplotlib.pyplot as plt

def callback(value):
    pass

cv.namedWindow('color', cv.WINDOW_NORMAL)
cv.resizeWindow('color', 640, 480)

img = cv.imread('/home/zack/图片/wallPaper/wallhaven-v95eml.jpg')

colorspace = [cv.COLOR_BGR2BGRA, cv.COLOR_BGR2GRAY, cv.COLOR_BGR2HSV, cv.COLOR_BGR2YUV]

cv.createTrackbar('curcolor', 'color', 0, 3, callback)

while True:
    index = cv.getTrackbarPos('curcolor', 'color')

    cvt_img = cv.cvtColor(img, colorspace[index])
    cv.imshow('color', cvt_img)

    key = cv.waitKey(10)
    if key == ord('q'):
        break

cv.destroyAllWindows()