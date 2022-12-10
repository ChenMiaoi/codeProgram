#include <iostream>
#include <opencv4/opencv2/opencv.hpp>

int main() {
    cv::VideoCapture capture(0);
    capture.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    capture.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    if (!capture.isOpened()) {
        std::cout << "open camera error!" << std::endl;
        return 1;
    }

    cv::Mat frame;
    while (true) {
        capture >> frame;
        if (frame.empty()) {
            std::cout << "capature empty frame" << std::endl;
            continue;
        }

        cv::Mat shrink_frame;
        cv::resize(frame, shrink_frame,
                   cv::Size(frame.cols / 2, frame.rows / 2),
                   0, 0, 3);
        cv::imshow("test", shrink_frame);

        int key = cv::waitKey(1);
        if (key == 'q')
            break;
    }
    return 0;
}