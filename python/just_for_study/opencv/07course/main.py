import numpy as np
import matplotlib.pyplot as plt
import cv2 as cv

# 背景去除案例
# cap = cv.VideoCapture(0)
#
# mog = cv.createBackgroundSubtractorMOG2()
#
# while cap.isOpened():
#     ret, frame = cap.read()
#
#     if ret == True:
#         fgmask = mog.apply(frame)
#         cv.imshow('video', fgmask)
#
#     key = cv.waitKey(1)
#     if key == 27:
#         break
# cap.release()
# cv.destroyAllWindows()

# 加载视频
cap = cv.VideoCapture("./Cars.mp4")

# 创建mog对象
mog = cv.createBackgroundSubtractorMOG2()

# 获取形态学卷积
kernel = cv.getStructuringElement(cv.MORPH_RECT, (5, 5))

# 设置矩形阈值
min_w = 120
min_h = 150

# 标识线的高度
line_high = 700

# 计算外接矩形的中心点
def center(x, y, w, h):
    x1 = int(w / 2)
    y1 = int(h / 2)
    cx = int(x) + x1
    cy = int(y) + y1
    return cx, cy

# 中心点偏移量
offset = 5

cars = []
carnums = 0

# 循环读取视频
while True:
    ret, frame = cap.read()
    if ret == True:
        # 进行灰度处理，然后高斯去噪
        gray = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)
        blur = cv.GaussianBlur(gray, (3, 3), 5)
        #blur = cv.medianBlur(gray, 3) # 中值
        #blur = cv.bilateralFilter(gray, 3, 20, 15) # 双边
        fgmask = mog.apply(blur)

        # # 腐蚀操作
        # erode = cv.erode(fgmask, kernel)
        # # 膨胀操作
        # dila = cv.dilate(erode, kernel, iterations=2)
        # 开运算
        open = cv.morphologyEx(fgmask, cv.MORPH_OPEN, kernel)

        # 闭运算
        close = cv.morphologyEx(open, cv.MORPH_CLOSE, kernel)

        # 查找轮廓
        contours, h = cv.findContours(close, cv.RETR_TREE, cv.CHAIN_APPROX_SIMPLE)

        # 画出标识线
        cv.line(frame, (10, line_high), (2000, line_high), (255, 255, 0), 2)

        # 画出所有轮廓,坐标点要保证是整数
        for contour in contours:
            # 最大外接矩形
            (x, y, w, h) = cv.boundingRect(contour)
            # 通过外接矩形的宽高来过滤小矩形
            is_valid = (w >= min_w) & (h >= min_h)
            if not is_valid:
                continue
            cv.rectangle(frame, (np.round(x), np.round(y)), (np.round(x + w), np.round(y + h)), (0, 0, 255), 2)

            # 就统计数量，把车看作一个点，即外接矩形的中心点
            cpoint = center(x, y, w, h)
            cars.append(cpoint)
            cv.circle(frame, (cpoint), 3, (0, 0, 255), -1)

            # 判断汽车是否过线
            for (x, y) in cars:
                if y > (line_high - offset) and y < (line_high + offset):
                    carnums += 1
                    cars.remove((x, y))
        cv.putText(frame, "Vehicle Count: " + str(carnums), (600, 60), cv.FONT_HERSHEY_SIMPLEX, 2, (0, 0, 255), 5)
        cv.imshow('video', frame)

    key = cv.waitKey(1)
    if key == 27:
        break

cap.release()
cv.destroyAllWindows()