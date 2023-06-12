#include <iostream>
#include "opencv2/opencv.hpp"

int main() {
    cv::Mat img = cv::imread("/home/dezi/Pictures/lena.jpeg");

    cv::Mat gray;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
    cv::Mat img_B, img_B_V, gray_B, gray_B_V, gray_T, gray_T_V, gray_TRUNC;

    // 彩色图像二值化
    cv::threshold(img, img_B, 125, 255, cv::THRESH_BINARY);
    cv::threshold(img, img_B_V, 125, 255, cv::THRESH_BINARY_INV);
    cv::imshow("img_B", img_B);
    cv::imshow("img_B_V", img_B_V);

    // 灰度图二值化
    cv::threshold(gray, gray_B, 125, 255, cv::THRESH_BINARY);
    cv::threshold(gray, gray_B_V, 125, 255, cv::THRESH_BINARY_INV);
    cv::imshow("gray_B", gray_B);
    cv::imshow("gray_B_V", gray_B_V);

    // 灰度图像TOZERO变换
    cv::threshold(gray, gray_T, 125, 255, cv::THRESH_TOZERO);
    cv::threshold(gray, gray_T_V, 125, 255, cv::THRESH_TOZERO_INV);
    cv::imshow("gray_T", gray_T);
    cv::imshow("gray_T_V", gray_T_V);

    // 灰度图TRUNC变换
    cv::threshold(gray, gray_TRUNC, 125, 255, cv::THRESH_TRUNC);
    cv::imshow("gray_TRUNC", gray_TRUNC);

    // 灰度大津法和三角形法
    cv::Mat img_Thr = cv::imread("/home/dezi/Pictures/shadow.jpeg", cv::IMREAD_GRAYSCALE);
    cv::Mat img_Thr_0, img_Thr_T;
    cv::threshold(img_Thr, img_Thr_0, 100, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
    cv::threshold(img_Thr, img_Thr_T, 125, 255, cv::THRESH_BINARY | cv::THRESH_TRIANGLE);
    cv::imshow("img_Thr", img_Thr);
    cv::imshow("img_Thr_0", img_Thr_0);
    cv::imshow("img_Thr_T", img_Thr_T);

    cv::Mat adaptive_mean, adapative_gauss;
    cv::adaptiveThreshold(img_Thr, adaptive_mean, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, 55, 0);
    cv::adaptiveThreshold(img_Thr, adapative_gauss, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 55, 0);
    cv::imshow("adapative_mean", adaptive_mean);
    cv::imshow("adapative_gauss", adapative_gauss);
    cv::waitKey();
    return 0;
}
