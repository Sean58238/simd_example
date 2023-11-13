/*
AVX512 demo
g++ --std=c++14 -O2 -mavx512 avx512_demo.cpp -o avx512_demo
Lin,Xiang
*/


#include <iostream>
#include <immintrin.h> // 包含 AVX-512 指令集头文件

 float A[256];
 float B[256];

void init()
{
	for(int i = 1; i <= 256; i++)
	{
		A[i] = (float)rand()/(float)RAND_MAX;
		B[i] = (float)rand()/(float)RAND_MAX;
	}
}


void matrix_addition_avx512(float *A, float *B, float *C, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j += 16) { // 每次处理 16 个元素（AVX-512 可以处理 512 位，即 16 个单精度浮点数）
            __m512 vecA = _mm512_loadu_ps(&A[i * size + j]);
            __m512 vecB = _mm512_loadu_ps(&B[i * size + j]);
            __m512 vecC = _mm512_add_ps(vecA, vecB);
            _mm512_storeu_ps(&C[i * size + j], vecC);
        }
    }
}

int main() {
    int size = 16; // 假设矩阵大小为 16x16
    float C[256] = {0}; // 结果矩阵 C
    init();
    matrix_addition_avx512(A, B, C, size);

    // 输出结果
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << C[i * size + j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}