#include <stdio.h>
#include <math.h>

// 所给函数
double f(double x) {
	return pow(3, x) - x * x * x;
}

int main() {
	double point1, point2; // 函数上的两个点
	double prec;// 精度
	printf("输入第一个点：");
	scanf("%lf", &point1);
	printf("输入第二个点：");
	scanf("%lf", &point2);
	printf("输入精度：");
	scanf("%lf", &prec);
	while (1) {
		// 新产生的两个点
		double newpoint1 = point2 - 0.618 * (point2 - point1);
		double newpoint2 = point1 + point2 - newpoint1;
		if (f(newpoint1) < f(newpoint2)) {
			point2 = newpoint2;
		}
		else {
			point1 = newpoint1;
		}
		if (point2 - point1 < prec) {
			printf("近似最小值为%lf", (point1 + point2) / 2);
			return 0;
		}
	}
}