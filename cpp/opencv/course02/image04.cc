#include <iostream>
#include <vector>
#include "opencv2/opencv.hpp"

int main() {
    cv::Mat img = cv::imread("/home/dezi/Pictures/lena.jpeg");
    
    cv::Mat img32;
    img.convertTo(img32, CV_32F, 1 / 255.0, 0);

    cv::Mat Gray0, Gray1;
    cv::cvtColor(img, Gray0, cv::COLOR_BGR2GRAY);
    cv::cvtColor(img, Gray1, cv::COLOR_RGB2GRAY);

    cv::Mat imgs[3];
    cv::split(img, imgs);
    cv::Mat img0, img1, img2;

    img0 = imgs[0];
    img1 = imgs[1];
    img2 = imgs[2];

    std::cout << img0 << std::endl;
    std::cout << img1 << std::endl;
    std::cout << img2 << std::endl;

    cv::Mat img_merge;
    cv::merge(imgs, 3, img_merge);

    cv::Mat zero = cv::Mat::zeros(cv::Size(img.cols, img.rows), CV_8U);
    std::vector<cv::Mat> imgs_v;
    // imgs_v.emplace_back(img0, zero, zero);
    imgs_v.push_back(img0);
    imgs_v.push_back(zero);
    imgs_v.push_back(zero);
    cv::Mat imgs_vmerge;
    cv::merge(imgs_v, imgs_vmerge);
    return 0;
}