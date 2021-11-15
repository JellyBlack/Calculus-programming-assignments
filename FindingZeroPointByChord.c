#include <stdio.h>
#include <math.h>

// 所给函数
double f(double x) {
	return 2 * pow(x, 5) + 6 * x - 7;
}

int main() {
	double a, b, prec;
	printf("输入初始区间左端点：");
	scanf("%lf", &a);
	printf("输入初始区间右端点：");
	scanf("%lf", &b);
	printf("输入精度：");
	scanf("%lf", &prec);
	if (f(a) * f(b) >= 0) {
		printf("无法在所给区间上求函数零点\n");
		return 0;
	}
	double point = a;
	double delta = b - a;
	while (delta >= prec) { // 两次求得的零点值之差小于精度，则终止
		double point2 = a - (b - a) / (f(b) - f(a)) * f(a); // 用弦截法求得的点
		delta = fabs(point2 - point);
		point = point2;
		// 上述点的函数值和左端点的函数值同号
		if (f(point) * f(a) > 0) {
			a = point;
		}
		else {
			b = point;
		}
	}
	printf("近似根为%lf\n", point);
	return 0;
}