#include <iostream>
#include "opencv2/opencv.hpp"

int main() {
    cv::Mat img = cv::imread("~/Picture/lena.jpg");
    
    cv::Mat img32;
    img.convertTo(img32, CV_32F, 1 / 255.0, 0);

    cv::Mat HSV, HSV32;
    cv::cvtColor(img, HSV, cv::COLOR_BGR2HSV);
    cv::cvtColor(img32, HSV32, cv::COLOR_BGR2HSV);

    cv::Mat Gray0, Gray1;
    cv::cvtColor(img, Gray0, cv::COLOR_BGR2GRAY);
    cv::cvtColor(img, Gray1, cv::COLOR_RGB2GRAY);
    return 0;
}