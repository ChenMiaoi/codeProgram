import numpy as np
import matplotlib.pyplot as plt
import cv2 as cv

img = cv.imread('/home/zack/图片/wallPaper/wallhaven-v95eml.jpg')

cv.namedWindow('img', cv.WINDOW_NORMAL)
cv.resizeWindow('img', (640, 480))

# kernel = np.ones((5, 5), np.float32) / 25
# kernel = np.array([[-1, -1, -1], [-1, 8, -1], [-1, -1, -1]])
# new_img = cv.filter2D(img, -1, kernel)

# new_img = cv.boxFilter(img, -1, (3, 3), normalize=True)

# new_img = cv.GaussianBlur(img, (3, 3), sigmaX=1)

new_img = cv.bilateralFilter(img, 7, 20, 20)
cv.imshow('img', np.hstack((new_img, img)))

key = cv.waitKey(0)
if key == ord('q'):
    cv.destroyAllWindows()