#include <stdio.h>
#include <math.h>

#define E 2.7182818284590452353602874713527

// 三维点
typedef struct {
	double x;
	double y;
	double z;
} Point;

// 所求函数
double f(Point point) {
	double x = point.x;
	double y = point.y;
	double z = point.z;
	return pow(2 * x + y - 3 * z + 7, 2) + pow(x * x + x * y + pow(E, z), 2);
}

// 计算所求函数的梯度
Point getGradient(Point point) {
	double x = point.x;
	double y = point.y;
	double z = point.z;
	Point newPoint;
	newPoint.x = 4 * (2 * x + y - 3 * z + 7) + 2 * (x * x + x * y + pow(E, z)) * (2 * x + y);
	newPoint.y = 2 * (2 * x + y - 3 * z + 7) + 2 * x * (x * x + x * y + pow(E, z));
	newPoint.z = -6 * (2 * x + y - 3 * z + 7) + 2 * (x * x + x * y + pow(E, z)) * pow(E, z);
	return newPoint;
}

// 向量加上另一个向量的常数倍
inline Point addVector(Point point, double constant, Point vector) {
	point.x += constant * vector.x;
	point.y += constant * vector.y;
	point.z += constant * vector.z;
	return point;
}

// 向量取模
inline double getModulo(Point point) {
	return sqrt(point.x * point.x + point.y * point.y + point.z * point.z);
}

// 0.618法计算一元函数的最小值，返回最小值点
double findMinimum(Point x, Point y, double step, double prec) {
	// 产生初始的两个t值，一值为0，另一值为步长的10倍
	double t1 = 0;
	double t2 = step * 10;
	while (1) {
		// 新产生的两个t值
		double newt1 = t2 - 0.618 * (t2 - t1);
		double newt2 = t1 + t2 - newt1;
		// 参与函数计算的点
		Point point1 = addVector(x, newt1, y);
		Point point2 = addVector(x, newt2, y);
		// 距离小于精度，则返回
		if (fabs(newt2 - newt1) <= prec) {
			return (t1 + t2) / 2;
		}
		if (f(point1) < f(point2)) {
			t2 = newt2;
		}
		else {
			t1 = newt1;
		}
	}
}

void main() {
	double prec = 1e-8; // 精度
	double step = 0.02; // 步长
	printf("精度：%.8lf，步长：%lf\n", prec, step);
	double multiple = 8; // multiple * prec 为精确搜索和粗略搜索的分界点
	Point x = { 1, -5, 1 }; // 初始点
	Point y = getGradient(x);
	y = addVector(y, -2, y); // 取相反向量
	int cursorySearch = 0, preciseSearch = 0; // 记录搜索次数
	Point old_x = x; // 保存上一次计算的x值，便于比较精度
	double modulo = multiple * prec + 1; // 使第一次使用粗略搜索
	while (1) {
		// 粗略搜索
		if (modulo >= multiple * prec) {
			x = addVector(x, step, y);
			cursorySearch++;
		}
		// 精确搜索
		else {
			double t0 = findMinimum(x, y, step, prec);
			x = addVector(x, t0, y);
			preciseSearch++;
		}
		// 计算两次x值差的模
		modulo = getModulo(addVector(x, -1, old_x));
		if (modulo <= prec) {
			break;
		}
		else {
			old_x = x;
		}
		y = getGradient(x);
		y = addVector(y, -2, y); // 取相反向量
	}
	printf("近似最优解：\nx = %lf\ny = %lf\nz = %lf\n", x.x, x.y, x.z);
	printf("性能：粗略搜索%d次，精确搜索%d次", cursorySearch, preciseSearch);
}