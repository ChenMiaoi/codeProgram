#include <iostream>
#include <ctime>
#include "eigen3/Eigen/Core"
#include "eigen3/Eigen/Dense"

#define MATRIX_SIZE 50

int main() {
    Eigen::Matrix<float, 2, 3> matrix_23;
    Eigen::Vector3d v_3d;
    Eigen::Matrix3d matrix_33 = Eigen::Matrix3d::Zero();
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> matrix_dynamic;
    Eigen::MatrixXd matrix_x;

    matrix_23 << 1, 2, 3, 4, 5, 6;
    std::cout << matrix_23 << std::endl;

    for (int i = 0; i < 1; i++) {
        for (int j = 0; j < 2; j++)
            std::cout << matrix_23(i, j) << " ";
        std::cout << "\n";
    }

    v_3d << 3, 2, 1;
    
    // Eigen::Matrix<double, 2, 1> result_wrong_type = matrix_23 * v_3d;
    Eigen::Matrix<double, 2, 1> result = matrix_23.cast<double>() * v_3d;
    std::cout << result << std::endl;

    matrix_33 = Eigen::Matrix3d::Random();
    std::cout << matrix_33 << std::endl;
    std::cout << matrix_33.transpose() << std::endl;
    std::cout << matrix_33.sum() << std::endl;
    std::cout << matrix_33.trace() << std::endl;
    std::cout << 10 * matrix_33 << std::endl;
    std::cout << matrix_33.inverse() << std::endl;
    std::cout << matrix_33.determinant() << std::endl;

    Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> eigen_solver(matrix_33.transpose() * matrix_33);
    std::cout << "Eigen value: " << eigen_solver.eigenvalues() << std::endl;
    std::cout << "Eigen vectors: " << eigen_solver.eigenvectors() << std::endl;

    Eigen::Matrix<double, MATRIX_SIZE, MATRIX_SIZE> matrix_NN;
    matrix_NN = Eigen::MatrixXd::Random(MATRIX_SIZE, MATRIX_SIZE);
    Eigen::Matrix<double, MATRIX_SIZE, 1> v_Nd;
    v_Nd = Eigen::MatrixXd::Random(MATRIX_SIZE, 1);

    clock_t tiem_stt = clock();
    Eigen::Matrix<double, MATRIX_SIZE, 1> x = matrix_NN.inverse() * v_Nd;
    std::cout << "tiome use in normal invers is: " << 1000 * (clock() - tiem_stt) / (double)CLOCKS_PER_SEC << "ms" << std::endl;

    tiem_stt = clock();
    x = matrix_NN.colPivHouseholderQr().solve(v_Nd);
    std::cout << "tiome use in Qr compsition invers is: " << 1000 * (clock() - tiem_stt) / (double)CLOCKS_PER_SEC << "ms" << std::endl;

    return 0;
}