/*
AVX2 demo
g++ --std=c++14 -O2 -mavx2 avx2_demo.cpp -o avx2_demo
Lin,Xiang
*/

#include <iostream>
#include <immintrin.h> // 包含 AVX2 指令集头文件

void matrix_addition_avx2_int(int *A, int *B, int *C, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j += 8) { // 每次处理 8 个元素（AVX2 可以处理 256 位，即 8 个 int32 整数）
            __m256i vecA = _mm256_loadu_si256((__m256i *)&A[i * size + j]);
            __m256i vecB = _mm256_loadu_si256((__m256i *)&B[i * size + j]);
            __m256i vecC = _mm256_add_epi32(vecA, vecB);
            _mm256_storeu_si256((__m256i *)&C[i * size + j], vecC);
        }
    }
}

int main() {
    int size = 8; // 假设矩阵大小为 8x8
    int A[64] = { 0, 1, 2, 3, 4, 5, 6, 7,
                  0, 1, 2, 3, 4, 5, 6, 7,
                  0, 1, 2, 3, 4, 5, 6, 7,
                  0, 1, 2, 3, 4, 5, 6, 7,
                  0, 1, 2, 3, 4, 5, 6, 7,
                  0, 1, 2, 3, 4, 5, 6, 7,
                  0, 1, 2, 3, 4, 5, 6, 7,
                  0, 1, 2, 3, 4, 5, 6, 7,
                  }; // 初始化矩阵 A

    int B[64] = { 0, 1, 2, 3, 4, 5, 6, 7, 
                  0, 1, 2, 3, 4, 5, 6, 7,
                  0, 1, 2, 3, 4, 5, 6, 7,
                  0, 1, 2, 3, 4, 5, 6, 7,
                  0, 1, 2, 3, 4, 5, 6, 7,
                  0, 1, 2, 3, 4, 5, 6, 7,
                  0, 1, 2, 3, 4, 5, 6, 7,
                  0, 1, 2, 3, 4, 5, 6, 7,
                }; // 初始化矩阵 B

    int C[64] = {0}; // 结果矩阵 C

    matrix_addition_avx2_int(A, B, C, size);

    // 输出结果
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << C[i * size + j] << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}