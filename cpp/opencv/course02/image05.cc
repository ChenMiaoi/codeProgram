#include <iostream>
#include "opencv2/opencv.hpp"

int main() {
    cv::Mat a = (cv::Mat_<uchar>(1, 2) << 0, 5);
    cv::Mat b = (cv::Mat_<uchar>(1, 2) << 0, 6);

    cv::Mat Xor, Or, Not, And;
    cv::bitwise_not(a, Not);
    cv::bitwise_and(a, b, And);
    cv::bitwise_or(a, b, Or);
    cv::bitwise_xor(a, b, Xor);

    std::cout << "a not: " << Not << std::endl;
    std::cout << "a and b: " << And << std::endl;
    std::cout << "a or b: " << Or << std::endl;
    std::cout << "a xor b: " << Xor << std::endl;
    return 0;
}