#include <iostream>
#include "opencv2/opencv.hpp"

int main() {
    cv::VideoCapture video;
    video.open(0);
    if (video.isOpened()) {
        std::cerr << "请检查视频文件" << "\n";
        exit(-1);
    }
    std::cout << "fps: " << video.get(cv::CAP_PROP_FPS) << std::endl;
    std::cout << "width: " << video.get(cv::CAP_PROP_FRAME_WIDTH) << std::endl;

    while (true) {
        cv::Mat frame;
        video >> frame;
        if (frame.empty()) {
            break;
        }
        cv::imshow("video", frame);

        uchar key = cv::waitKey(1000 / cv::CAP_PROP_FPS);
        if (key == 'q') break;
    }
    return 0;
}