#include <Eigen/Dense>
#include <iostream>
#include <chrono>

int main() {
    int dim = 512;
    Eigen::MatrixXd A = Eigen::MatrixXd::Random(dim, dim);
    Eigen::MatrixXd B = Eigen::MatrixXd::Random(dim, dim);

    auto start = std::chrono::high_resolution_clock::now();
    Eigen::MatrixXd C = A * B;
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;

    std::cout << "Matrix multiplication using Eigen completed." << std::endl;
    std::cout << "Time taken: " << elapsed_seconds.count() << " seconds" << std::endl;
    return 0;
}