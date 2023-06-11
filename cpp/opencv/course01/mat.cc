#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    cv::Mat a(3, 3, CV_8UC1);
    cv::Mat B(cv::Size(4, 4), CV_8UC1);

    cv::Mat c0(5, 5, CV_8UC1, cv::Scalar(4, 5, 6));
    cv::Mat c1(5, 5, CV_8UC2, cv::Scalar(4, 5, 6));
    cv::Mat c2(5, 5, CV_8UC3, cv::Scalar(4, 5, 6));

    cv::Mat d = (cv::Mat_<int>(1, 5) << 1, 2, 3, 4, 5);

    cv::Mat e = cv::Mat::diag(d);

    cv::Mat f = cv::Mat(e, cv::Range(2, 4), cv::Range(2, 4));

    std::cout << c0 << "\n";
    std::cout << c1 << "\n";
    std::cout << c2 << "\n";
    std::cout << d << "\n";
    std::cout << e << "\n";
    std::cout << f << "\n";

    cv::Mat aa =(cv::Mat_<int>(3, 3) << 1, 2, 3, 4, 5, 6, 7, 8, 9);

    std::cout << aa.at<int>(0, 0) << "\n";
    cv::Vec2b vc = c1.at<cv::Vec2b>(0, 1);
    std::cout << vc << "\n";
    std::cout << (int)vc[0] << "\n";

    std::cout << (int)c0.at<uchar>(0, 0) << "\n";
    return 0;
}
 