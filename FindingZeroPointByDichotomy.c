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
	while (b - a >= prec) {
		double midpoint = (a + b) / 2; // 中点
		// 中点的函数值和左端点的函数值同号
		if (f(midpoint) * f(a) > 0) {
			a = midpoint;
		}
		else {
			b = midpoint;
		}
	}
	printf("近似根为%lf\n", (a + b) / 2);
	return 0;
}