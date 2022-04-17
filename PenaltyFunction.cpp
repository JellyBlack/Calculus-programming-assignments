#include <stdio.h>
#include <math.h>

#define E 2.7182818284590452353602874713527

// 三维点/向量
class Vector {
	public:
		// 三个分量
		double x;
		double y;
		double z;

		// 重载向量运算+（C++）
		Vector operator+(const Vector another) {
			Vector vector;
			vector.x = x + another.x;
			vector.y = y + another.y;
			vector.z = z + another.z;
			return vector;
		}

		// 重载向量运算-（C++）
		Vector operator-(const Vector another) {
			Vector vector;
			vector.x = x - another.x;
			vector.y = y - another.y;
			vector.z = z - another.z;
			return vector;
		}

		// 重载向量运算*（点乘）（C++）
		Vector operator*(const Vector another) {
			Vector vector;
			vector.x = x * another.x;
			vector.y = y * another.y;
			vector.z = z * another.z;
			return vector;
		}

		// 重载向量运算*（数乘）（C++）
		Vector operator*(const double num) {
			Vector vector;
			vector.x = x * num;
			vector.y = y * num;
			vector.z = z * num;
			return vector;
		}

		// 向量取模
		inline double getModulo() {
			return sqrt(x * x + y * y + z * z);
		}
};

// 向量取模
inline double getModulo(Vector vector) {
	return sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
}

// 目标函数
double f(Vector vector) {
	double x = vector.x;
	double y = vector.y;
	double z = vector.z;
	return x * x + y * y + z * z;
}

// 约束函数
double g(Vector vector) {
	return vector.x + 2 * vector.y + 3 * vector.z - 10;
}

// 0.618法计算一元函数的最小值，返回最小值点
double findMinimum(Vector x, Vector y, double min, double max, double prec, double factor) {
	// 产生初始的两个t值
	double t1 = min;
	double t2 = max;
	while (1) {
		// 新产生的两个t值
		double newt1 = t2 - 0.618 * (t2 - t1);
		double newt2 = t1 + t2 - newt1;
		// 参与函数计算的点
		Vector Vector1 = x + y * newt1;
		Vector Vector2 = x + y * newt2;
		// 距离小于精度，则返回
		if (fabs(newt2 - newt1) <= prec) {
			return (t1 + t2) / 2;
		}
		if (f(Vector1) + factor * g(Vector1) * g(Vector1) < f(Vector2) + factor * g(Vector2) * g(Vector2)) {
			t2 = newt2;
		}
		else {
			t1 = newt1;
		}
	}
}

int count1 = 0, count2 = 0; // 性能计数

// 给定罚因子，计算最优解
Vector optimize(double factor) {
	double prec = 1e-8; // 搜索精度
	double result_prec = 1e-8; // 结果精度
	double step = 0.2; // 步长
	Vector x = { 0,0,0 }; // 初始点
	while (1) {
		count1++;
#ifdef DEBUG
		printf("第%d次轮换：\n", count1);
		printf("起始点：%lf, %lf, %lf\n", x.x, x.y, x.z);
#endif
		// 三个坐标轴上的单位向量
		Vector e1 = { 1,0,0 };
		Vector e2 = { 0,1,0 };
		Vector e3 = { 0,0,1 };
		// 坐标轮换，搜索最小值
		double t1 = findMinimum(x, e1, -step, step, prec, factor);
		Vector x1 = x + e1 * t1;
		double t2 = findMinimum(x1, e2, -step, step, prec, factor);
		Vector x2 = x1 + e2 * t2;
		double t3 = findMinimum(x2, e3, -step, step, prec, factor);
		Vector x3 = x2 + e3 * t3; // x3为本次坐标轮换搜索到的最小值
#ifdef DEBUG
		printf("轮换结果：%lf, %lf, %lf\n", x3.x, x3.y, x3.z);
		printf("函数值：%lf\n", f(x3));
		printf("模长之差：%lf\n", getModulo(x3 - x));
#endif
		// 判断是否满足终止条件
		if (getModulo(x3 - x) <= result_prec) {
			return x3;
		}
		// 从x到x3再进行一维搜索
		Vector d = x3 - x; // 从x指向x3的向量
		double t = findMinimum(x, d, 0, 1, prec, factor); // 一维搜索
		x = x + d * t; // 将搜索结果置为x，开始下一次坐标轮换
	}
}

void main() {
	double prec = 1e-6; // 针对精度的约束值
	double factor = 10;
	while (1) {
		count2++;
		Vector result = optimize(factor);
		printf("第%d次优化：x=%lf, y=%lf, z=%lf\n", count2, result.x, result.y, result.z);
		printf("目标函数值：%lf\n", f(result));
		printf("约束函数值：%lf\n", g(result));
		if (g(result) * g(result) <= prec) {
			printf("\n\n近似最优解：x=%lf, y=%lf, z=%lf\n", result.x, result.y, result.z);
			printf("目标函数值：%lf\n", f(result));
			printf("约束函数值：%lf\n", g(result));
			printf("性能：优化%d次，共搜索%d次", count2, count1);
			return;
		}
		// 即将超过double最大值，终止计算
		if (factor > 1e290) {
			printf("未在罚因子不超过double最大值的前提下找到最优解\n");
			return;
		}
		factor *= 1e10;
	}
}
