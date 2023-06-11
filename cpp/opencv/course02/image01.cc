#include <iostream>
#include <vector>
#include "opencv2/opencv.hpp"

int main() {
    cv::Mat img = cv::imread("~/Picture/lena.jpg", cv::IMREAD_COLOR);
    cv::Mat gray = cv::imread("~/Picture/lena.jpg", cv::IMREAD_GRAYSCALE);

    cv::namedWindow("img", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("grey", cv::WINDOW_NORMAL);

    cv::imshow("img", img);
    cv::imshow("grey", gray);

    std::vector<int> compress_params;
    compress_params.push_back(cv::IMWRITE_PNG_COMPRESSION);
    compress_params.push_back(9);
    cv::imwrite("./new_lena.png", img, compress_params);
    cv::waitKey(0);
    return 0;
}