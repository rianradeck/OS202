#include <cblas.h>
#include <vector>
#include <iostream>
#include <chrono>

void prodMatMatBLAS(const std::vector<double>& A, const std::vector<double>& B, std::vector<double>& C, int M, int N, int K) {
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, M, N, K, 1.0, A.data(), K, B.data(), N, 0.0, C.data(), N);
}

int main() {
    int M = 512, N = 512, K = 512;
    std::vector<double> A(M * K, 1.0);
    std::vector<double> B(K * N, 1.0);
    std::vector<double> C(M * N, 0.0);

    auto start = std::chrono::high_resolution_clock::now();
    prodMatMatBLAS(A, B, C, M, N, K);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;

    std::cout << "Matrix multiplication using BLAS completed." << std::endl;
    std::cout << "Time taken: " << elapsed_seconds.count() << " seconds" << std::endl;
    return 0;
}