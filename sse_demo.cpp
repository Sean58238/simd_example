/*
sse4.2 demo
g++ --std=c++14 -O2 -msse sse_demo.cpp -o sse_demo
Lin,Xiang
*/

#include <iostream>
#include <nmmintrin.h> // 包含 SSE4.2 指令集头文件

void matrix_addition_sse_int(int *A, int *B, int *C, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j += 8) { // 每次处理 8 个元素（sse 可以处理 128 位，即 4 个 int32 整数）
            __m128i vecA = _mm_loadu_si128((__m128i *)&A[i * size + j]);
            __m128i vecB = _mm_loadu_si128((__m128i *)&B[i * size + j]);
            __m128i vecC = _mm_add_epi64(vecA, vecB);
            _mm_storeu_si128((__m128i *)&C[i * size + j], vecC);
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

    matrix_addition_sse_int(A, B, C, size);

    // 输出结果
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << C[i * size + j] << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}