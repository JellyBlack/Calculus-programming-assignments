#include <stdio.h>
#include <math.h>

int main() {
	double x = 6.0 / 7.0;
	double prec;
	printf("输入精度：");
	scanf("%lf", &prec);
	double sum = 0; // 近似和
	int k = 0;
	while (pow(x, k + 1) / (double)(k + 1) >= prec) {
		sum += pow(x, k + 1) / (double)(k + 1);
		k++;
	}
	printf("近似值为%lf\n", sum);
	return 0;
}