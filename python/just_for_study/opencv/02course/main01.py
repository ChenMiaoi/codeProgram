import numpy as np
import matplotlib.pyplot as plt
import cv2 as cv

img = np.zeros((480, 640, 3), np.uint8)


cv.line(img, (10, 20), (300, 400), (0, 0, 255), 5, 4)
cv.line(img, (80, 100), (380, 480), (0, 0, 255), 5, 16)

cv.rectangle(img, (10, 20), (300, 400), (0, 255, 0), 5)

cv.circle(img, (50, 60), 100, (255, 0, 0))

cv.ellipse(img, (300, 200), (100, 50), 0, 0, 360, [0, 0, 255], lineType=16)

pts = np.array([(250, 100), (300, 150), (100, 200)], np.int32)
cv.polylines(img, [pts], True, [0, 0, 255])

cv.putText(img, "Hello OpenCV", (200, 200), cv.FONT_HERSHEY_SIMPLEX, 2, (0, 0, 255))

cv.imshow('img', img)

key = cv.waitKey(0)
if key == ord('q'):
    cv.destroyAllWindows()