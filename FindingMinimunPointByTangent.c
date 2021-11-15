#include <stdio.h>
#include <math.h>

// 所给函数
double f(double x) {
	return pow(3, x) - x * x * x;
}

// 所给函数的导数
double deri(double x) {
	return pow(3, x) * 1.0986122886681096 - 3 * x * x;
}

int main() {
	double point1, point2; // 函数上的两个点
	double prec;// 精度
	printf("输入左端点：");
	scanf("%lf", &point1);
	printf("输入右端点：");
	scanf("%lf", &point2);
	printf("输入精度：");
	scanf("%lf", &prec);
	while (1) {
		double point = (f(point2) - f(point1) + deri(point1) * point1 - deri(point2) * point2) / (deri(point1) - deri(point2)); // 求出的点
		double deripoint = deri(point); // 求出的点的导数值
		if (fabs(point2 - point1) < prec) {
			printf("近似极小值点为%lf", point);
			return 0;
		}
		if (deripoint < 0) {
			point1 = point;
		}
		else {
			point2 = point;
		}
	}
}