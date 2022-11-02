import matplotlib.pyplot as plt
import numpy as np
import numpy as py
import cv2 as cv

img = cv.imread('/home/zack/图片/wallPaper/wallhaven-v95eml.jpg')

cv.namedWindow('img', cv.WINDOW_NORMAL)
cv.resizeWindow('img', 640, 480)

# kernel = np.ones((3, 3), np.uint8)
kernel = cv.getStructuringElement(cv.MORPH_RECT, (9, 9))
# new_img = cv.dilate(img, kernel, iterations=1)

new_img = cv.morphologyEx(img, cv.MORPH_BLACKHAT, kernel)

cv.imshow('img', np.hstack((img, new_img)))

key = cv.waitKey(0)
if key == ord('q'):
    cv.destroyAllWindows()