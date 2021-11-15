#include <stdio.h>
#include <math.h>
#define PI 3.141592653589793

// 所给函数的k阶导数
double f(double x, int k) {
	if (k % 4 == 0) {
		return sin(x);
	}
	if (k % 4 == 1) {
		return cos(x);
	}
	if (k % 4 == 2) {
		return -sin(x);
	}
	return -cos(x);
}

// 计算阶乘
int factorial(int num) {
	int result = 1;
	while (num > 1) {
		result *= num--;
	}
	return result;
}

int main() {
	double x = 37 * PI / 180;
	double prec;
	printf("输入精度：");
	scanf("%lf", &prec);
	double sum = 0; // 近似和
	int k = 0;
	while (pow(x, k + 1) / (double)factorial(k + 1) >= prec) {
		sum += f(0, k) * pow(x, k) / (double)factorial(k);
		k++;
	}
	printf("近似值为%lf\n", sum);
	return 0;
}