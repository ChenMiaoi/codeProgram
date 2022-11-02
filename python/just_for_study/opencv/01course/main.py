import cv2 as cv
import matplotlib.pyplot as plt
import numpy as np

'''
cv.namedWindow('new', cv.WINDOW_NORMAL)
cv.resizeWindow('new', 800, 600)
cv.imshow('new', 0)
key = cv.waitKey()
if key == 'q':
    cv.destroyAllWindows()
'''
'''
img = cv.imread('/home/zack/图片/wallPaper/wallhaven-dgj3qj.jpg')
# plt.imshow(img)
cv.imshow('new', img)
key = cv.waitKey()
if key == 'q':
    cv.destroyAllWindows()
'''
'''
cv.namedWindow('img', cv.WINDOW_NORMAL)
cv.resizeWindow('img', 320, 240)

img = cv.imread('/home/zack/图片/wallPaper/wallhaven-dgj3qj.jpg')

while True:
    cv.imshow('img', img)
    key = cv.waitKey(0)
    if key & 0xFF == ord('q'):
        break
    elif key & 0xFF == ord('s') :
        cv.imwrite('img01.png', img)
    else:
        print(key)
cv.destroyAllWindows()
'''
'''
cv.namedWindow('video', cv.WINDOW_NORMAL)
cv.resizeWindow('video', 640, 480)

# cap = cv.VideoCapture(0)
cap = cv.VideoCapture('/home/zack/视频/vidio/Linux基础命令(完).mkv')

while cap.isOpened() :# True:
    ret, frame = cap.read()

    if not ret:
        break

    cv.imshow('video', frame)
    key = cv.waitKey(1000//60)
    if key & 0xFF == ord('q'):
        break
cap.release()
cv.destroyAllWindows()
'''

'''
cap = cv.VideoCapture(0)
fourcc = cv.VideoWriter_fourcc(*'mp4v')

vw = cv.VideoWriter('output.mp4', fourcc, 30, (640, 480))

while cap.isOpened():
    ret, frame = cap.read()
    if not ret:
        break

    vw.write(frame)
    cv.imshow('frame', frame)

    if cv.waitKey(1) == ord('q'):
        break

cap.release()
vw.release()
cv.destroyAllWindows()
'''

'''
def mouse_callback(event, x, y, flags, userdata):
    print(event, x, y, flags, userdata)
    if event == cv.EVENT_LBUTTONDOWN:
        cv.destroyAllWindows()

cv.namedWindow('mouse', cv.WINDOW_NORMAL)
cv.resizeWindow('mouse', 640, 360)

cv.setMouseCallback('mouse', mouse_callback, '123')
img = np.zeros((360, 640, 3), np.uint8)

while True:
    cv.imshow('mouse', img)
    key = cv.waitKey(1)
    if key == ord('q'):
        break

cv.destroyAllWindows()
'''

cv.namedWindow('trackbar', cv.WINDOW_NORMAL)
cv.resizeWindow('trackbar', 640, 480)

def callback(value):
    # print(value)
    pass

cv.createTrackbar('R', 'trackbar', 0, 255, callback)
cv.createTrackbar('B', 'trackbar', 0, 255, callback)
cv.createTrackbar('G', 'trackbar', 0, 255, callback)

img = np.zeros((480, 640, 3), np.uint8)

while True:
    r = cv.getTrackbarPos('R', 'trackbar')
    b = cv.getTrackbarPos('B', 'trackbar')
    g = cv.getTrackbarPos('G', 'trackbar')

    img[:] = [b, g, r]
    cv.imshow('trackbar', img)

    key = cv.waitKey(1)
    if key == ord('q'):
        break

cv.destroyAllWindows()