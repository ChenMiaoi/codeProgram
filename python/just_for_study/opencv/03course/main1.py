import numpy as np
import matplotlib.pyplot as plt
import cv2 as cv

img = cv.imread('/home/zack/图片/wallPaper/wallhaven-v95eml.jpg')
# print(img.shape)
#
# new_img = cv.resize(img, (640, 480))
# print(new_img.shape)

# new_img = cv.flip(img, flipCode=0)
# new_img = cv.resize(new_img, (640, 480))

# new_img = cv.rotate(img, cv.ROTATE_90_CLOCKWISE)
# new_img = cv.resize(new_img, (640, 700))
new_img = cv.resize(img, (640, 480))

# M = np.float32([[1, 0, 200], [0, 1, 0]])
h, w, ch = new_img.shape
#M = cv.getRotationMatrix2D((w/2, h/2), 45, 1.0)
src = np.float32([[200, 100], [300, 100], [200, 300]])
dst = np.float32([[100, 150], [360, 200], [280, 120]])
M = cv.getAffineTransform(src, dst)

new_img = cv.warpAffine(img, M, dsize=(w, h))
cv.imshow('img', new_img)
key = cv.waitKey(0)
if key == ord('q'):
    cv.destroyAllWindows()