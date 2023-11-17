/*
sse4.2 demo
g++ --std=c++14 -O2 -msse sse_demo2.cpp -o sse_demo2
Lin,Xiang
*/

#include <iostream>
#include <nmmintrin.h> // 包含 SSE4.2 指令集头文件

int main(){
    float x= 3.8f;
    float y= 3.8f;
    float z= 3.8f;
    float w= 3.8f;


    __m128 m = _mm_setr_ps(x, y, x, w);
    __m128 n = _mm_set1_ps(x);

    m = _mm_add_ps(m,n);
    //printf(m);

}