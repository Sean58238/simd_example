/*
sse4.2 compare demo
g++ --std=c++14 -O2 -msse sse_compare.cpp -o sse_compare
Lin,Xiang
*/

#include <iostream>
#include <nmmintrin.h>
#include <sys/time.h>

#define N 1'000'000

float op1[N];
float op2[N];
float result1[N];
float result2[N];

void init()
{
	for (int i = 0; i < N; i++)
	{
		op1[i] = (float)rand() / (float)RAND_MAX;
		op2[i] = (float)rand() / (float)RAND_MAX;
	}
}

#pragma loop(no_vector)
void add()
{
	for (int i = 0; i < N; i++)
	{
		result1[i] = op1[i] + op2[i];
	}
}

void add_sse()
{
	__m128 a;
	__m128 b;
	__m128 c;

	for (int i = 0; i < N; i = i + 4)
	{
		// Load
		a = _mm_loadu_ps(op1 + i);
		b = _mm_loadu_ps(op2 + i);

		c = _mm_add_ps(a, b); // c = a + b

		_mm_storeu_ps(result2 + i, c);
	}
}

int main(int argc, char *argv[])
{
	init();
	// srand((unsigned int)time(NULL));

	struct timeval t1, t2;
	double timeuse;
	printf("Add a vector\n");

	gettimeofday(&t1, NULL);
	for (size_t i = 0; i < 10000; i++)
	{
		add();
	}
	add();
	gettimeofday(&t2, NULL);
	timeuse = (t2.tv_sec - t1.tv_sec) * 1000 + (double)(t2.tv_usec - t1.tv_usec) / 1000.0;
	std::cout << "Elapsed time (ms) : " << timeuse << std::endl; // 输出时间（单位：ms）

	printf("\n");
	printf("Add a vector with SSE4.2 instructions\n");
	gettimeofday(&t1, NULL);
	for (size_t i = 0; i < 10000; i++)
	{
		// add_sse();
	}
	gettimeofday(&t2, NULL);
	timeuse = (t2.tv_sec - t1.tv_sec) * 1000 + (double)(t2.tv_usec - t1.tv_usec) / 1000.0;
	std::cout << "Elapsed time (ms): " << timeuse << std::endl; // 输出时间（单位：ms）

	return 0;
}