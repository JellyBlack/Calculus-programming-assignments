#include <stdio.h>
#include <math.h>

// 所给函数
double f(double x) {
	return pow(3, x) - x * x * x;
}

int main() {
	double point1, point2; // 函数上的两个点
	double step; // 步长
	double prec;// 精度
	printf("输入一个点：");
	scanf("%lf", &point1);
	printf("输入步长：");
	scanf("%lf", &step);
	printf("输入精度：");
	scanf("%lf", &prec);
	point2 = point1 + step;
	while (1) {
		if (f(point2) < f(point1)) {
			step *= 2;
			point1 = point2;
			point2 += step;
		}
		else {
			step *= -0.2;
			double temp = point1;
			point1 = point2;
			point2 = temp;
			point1 += step;
		}
		if (fabs(point1 - point2) < prec) {
			printf("第一个点: %lf\n第二个点: %lf", point1, point2);
			return 0;
		}
	}
}