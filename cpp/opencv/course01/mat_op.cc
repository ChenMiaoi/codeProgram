#include <iostream>
#include "opencv2/opencv.hpp"

int main() {
    cv::Mat a = (cv::Mat_<int>(3, 3) << 1, 2, 3, 4, 5, 6, 7, 8, 9);
    cv::Mat b = (cv::Mat_<int>(3, 3) << 1, 2, 3, 7, 8, 9, 4, 5, 6);
    cv::Mat c = (cv::Mat_<double>(3, 3) << 1.0, 2.1, 3.2, 4.3, 5.4, 6.5, 7.6, 8.7, 9.8); 
    cv::Mat d = (cv::Mat_<double>(3, 3) << 1.0, 2.1, 3.2, 4.3, 5.4, 6.5, 7.6, 8.7, 9.8);

    std::cout << "matrix add: " << a + b << "\n";
    std::cout << "matrix sub: " << a - b << "\n";
    std::cout << "matrix mul: " << 2 * a << "\n";
    std::cout << "matrix div: " << d / 2.0 << "\n";
    std::cout << "sub int: " << a - 1 << "\n";

    std::cout << "two matrix mul: " << c * d << "\n";  
    std::cout << "two matrix inner mul: " << a.dot(b) << "\n";  
    std::cout << "two matrix mul: " << a.mul(b) << "\n";  

    std::cout << "two matrix min: " << cv::min(a, b) << "\n";
    return 0;
}