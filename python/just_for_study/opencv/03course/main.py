import numpy as np
import matplotlib.pyplot as plt
import cv2 as cv

img1 = cv.imread('/home/zack/图片/wallPaper/wallhaven-v95eml.jpg')
img2 = cv.imread('/home/zack/图片/wallPaper/wallhaven-dgj3qj.jpg')

print(img1.shape)
print(img2.shape)

cv.namedWindow('new_img', cv.WINDOW_NORMAL)
cv.resizeWindow('new_img', 640, 480)

# new_img = cv.add(img1, img2)
# new_img = cv.addWeighted(img1, 0.4, img2, 0.6, 0)

# new_img = cv.bitwise_not(img1, img2)
# new_img = cv.bitwise_and(img1, img2)
# new_img = cv.bitwise_or(img1, img2)
new_img = cv.bitwise_xor(img1, img2)

cv.imshow('new_img', new_img)
key = cv.waitKey(0)
if key == ord('q'):
    cv.destroyAllWindows()