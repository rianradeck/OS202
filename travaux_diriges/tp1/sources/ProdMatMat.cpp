#include <algorithm>
#include <cassert>
#include <iostream>
#include <thread>
#if defined(_OPENMP)
#include <omp.h>
#endif
#include "ProdMatMat.hpp"
// #include <map>

#define NUM_THREADS 1

namespace {
void prodSubBlocks(int iRowBlkA, int iColBlkB, int iColBlkA, int szBlock,
                   const Matrix& A, const Matrix& B, Matrix& C) {
  omp_set_num_threads(NUM_THREADS);
  // std::map<std::pair<int, int>, std::vector<std::pair<int, int>>> m;
  #pragma omp parallel for
  for (int j = iColBlkB; j < std::min(B.nbCols, iColBlkB + szBlock); j++)
    for (int k = iColBlkA; k < A.nbCols; k++)
      for (int i = iRowBlkA; i < std::min(A.nbRows, iRowBlkA + szBlock); ++i){
        // m[std::make_pair(i, j)].push_back(std::make_pair(i, k));
        // m[std::make_pair(i, j)].push_back(std::make_pair(k, j));
        C(i, j) += A(i, k) * B(k, j);
      }
  
  // for (int i = iRowBlkA; i < std::min(A.nbRows, iRowBlkA + szBlock); ++i)
  //   for (int j = iColBlkB; j < std::min(B.nbCols, iColBlkB + szBlock); j++){
  //     std::cout << "(" << i << ", " << j << ") -> ";
  //     for(auto [a, b] : m[std::make_pair(i, j)])
  //       std::cout << "(" << a << ", " << b << "); ";
  //   }
  // std::cout << "\n";
}
const int szBlock = 512;
}  // namespace

Matrix operator*(const Matrix& A, const Matrix& B) {
  Matrix C(A.nbRows, B.nbCols, 0.0);
  // #pragma omp parallel for
  for(int blocki = 0; blocki < A.nbRows/szBlock; blocki++)
    for(int blockj = 0;blockj < B.nbCols/szBlock; blockj++)
      prodSubBlocks(blocki * szBlock, blockj * szBlock, 0, szBlock, A, B, C);
  // prodSubBlocks(0, 0, 0, rows/2, A, B, C);
  // prodSubBlocks(0, rows/2, 0, rows/2, A, B, C);
  // prodSubBlocks(rows/2, 0, 0, rows/2, A, B, C);
  // prodSubBlocks(rows/2, rows/2, 0, rows/2, A, B, C);
  return C;
}