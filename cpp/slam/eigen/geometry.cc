#include <iostream>
#include "eigen3/Eigen/Dense"

int main() {
    // 3D旋转矩阵
    Eigen::Matrix3d rotation_matrix = Eigen::Matrix3d::Identity();  
    // 旋转向量，沿Z轴旋转了45°
    Eigen::AngleAxisd rotation_vector (M_PI / 4, Eigen::Vector3d(0, 0, 1));
    std::cout.precision(3);     // 设置输出精度，保留小数点后三位

    std::cout << "rotation matrix: \n" << rotation_vector.matrix() << std::endl;

    rotation_matrix = rotation_vector.toRotationMatrix();
    std::cout << "rotation matrix: \n" << rotation_matrix << std::endl;

    Eigen::Vector3d v(1, 0, 0);
    Eigen::Vector3d v_rotated = rotation_vector * v;
    std::cout << "(1, 0, 0) after rotation: " << v_rotated.transpose() << std::endl;

    v_rotated = rotation_matrix * v;
    std::cout << "(1, 0, 0) after rotation: " << v_rotated.transpose() << std::endl;

    Eigen::Vector3d euler_angles = rotation_matrix.eulerAngles(2, 1, 0); // 欧拉角ZYX顺序
    std::cout << "yaw pitch roll: " << euler_angles.transpose() << std::endl;

    Eigen::Isometry3d T = Eigen::Isometry3d::Identity();    //欧式变换矩阵，4*4
    T.rotate(rotation_vector);  //依照rotation_vector进行旋转
    T.pretranslate(Eigen::Vector3d(1, 3, 4));   // 将平移向量设置为(1, 3, 4)
    std::cout << "Transform matrix: \n" << T.matrix() << std::endl;

    // 变换矩阵进行坐标变换
    Eigen::Vector3d v_transformed = T * v;  // 相当于 R * v + t
    std::cout << "v transformed: " << v_transformed.transpose() << std::endl;

    // 四元数
    Eigen::Quaterniond q = Eigen::Quaterniond(rotation_vector);
    std::cout << "quaterniond: \n" << q.coeffs().transpose() << std::endl;  // coeffe顺序为(x, y, z, w)

    q = Eigen::Quaterniond(rotation_matrix);
    std::cout << "quaterniond: \n" << q.coeffs().transpose() << std::endl;  // coeffe顺序为(x, y, z, w)

    // 四元数旋转向量
    v_rotated = q * v;  // 在数学上是qvq^{-1}
    std::cout << "(1, 0, 0) after rotated: " << v_rotated.transpose() << std::endl;
    return 0;
}