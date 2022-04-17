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

// 所求函数
double f(Vector vector) {
	double x = vector.x;
	double y = vector.y;
	double z = vector.z;
	return pow(2 * x + y - 3 * z + 7, 2) + pow(x * x + x * y + pow(E, z), 2);
}

// 0.618法计算一元函数的最小值，返回最小值点
double findMinimum(Vector x, Vector y, double min, double max, double prec) {
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
		if (f(Vector1) < f(Vector2)) {
			t2 = newt2;
		}
		else {
			t1 = newt1;
		}
	}
}

void main() {
	double prec = 1e-8; // 精度
	double step = 0.2; // 步长
	printf("精度：%.8lf，步长：%lf\n", prec, step);
	Vector x = { 0,0,0 }; // 初始点
	int count = 0; // 性能计数
	while (1) {
		count++;
#ifdef DEBUG
		printf("第%d次轮换：\n", count);
		printf("起始点：%lf, %lf, %lf\n", x.x, x.y, x.z);
#endif
		// 三个坐标轴上的单位向量
		Vector e1 = { 1,0,0 };
		Vector e2 = { 0,1,0 };
		Vector e3 = { 0,0,1 };
		// 坐标轮换，搜索最小值
		double t1 = findMinimum(x, e1, -step, step, prec);
		Vector x1 = x + e1 * t1;
		double t2 = findMinimum(x1, e2, -step, step, prec);
		Vector x2 = x1 + e2 * t2;
		double t3 = findMinimum(x2, e3, -step, step, prec);
		Vector x3 = x2 + e3 * t3; // x3为本次坐标轮换搜索到的最小值
#ifdef DEBUG
		printf("轮换结果：%lf, %lf, %lf\n", x3.x, x3.y, x3.z);
		printf("函数值：%lf\n", f(x3));
		printf("模长之差：%lf\n", getModulo(x3 - x));
#endif
		// 判断是否满足终止条件
		if (getModulo(x3 - x) <= prec) {
			x = x3;
			break;
		}
		// 从x到x3再进行一维搜索
		Vector d = x3 - x; // 从x指向x3的向量
		double t = findMinimum(x, d, 0, 1, prec); // 一维搜索
		x = x + d * t; // 将搜索结果置为x，开始下一次坐标轮换
	}
	printf("近似最优解：\nx = %lf\ny = %lf\nz = %lf\n", x.x, x.y, x.z);
	printf("此点函数值：%lf\n", f(x));
	printf("性能：共轮换%d次", count);
}
