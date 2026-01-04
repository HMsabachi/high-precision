#ifndef HIGH_PRECISION_H
#define HIGH_PRECISION_H
#include <cmath>
#include <vector>
#include <string>


class HighPrecision {
private:
	std::vector<int> digits; // 值 以每位数字存储在向量中，最低位在前
public:
	HighPrecision(); // 默认构造函数，初始化为0
	HighPrecision(int number); // 从整数构造高精度数
	HighPrecision(const std::string& numberStr); // 从字符串构造高精度数
	HighPrecision(const HighPrecision& other); // 拷贝构造函数
	HighPrecision& operator=(const HighPrecision& other); // 拷贝赋值运算符
	HighPrecision(HighPrecision&& other) noexcept; // 移动构造函数
	HighPrecision& operator=(HighPrecision&& other) noexcept; // 移动赋值运算符
	~HighPrecision();

public:
	HighPrecision operator+(const HighPrecision& other) const;
	HighPrecision operator-(const HighPrecision& other) const;
	HighPrecision operator*(const HighPrecision& other) const;
	HighPrecision operator*(const int other) const;
	HighPrecision operator/(const HighPrecision& other) const;
	HighPrecision operator/(const int other) const;
	HighPrecision operator%(const HighPrecision& other) const;
	HighPrecision operator%(const int other) const;
	HighPrecision operator^(const HighPrecision& other) const; 
	HighPrecision operator^(const int other) const; 
	HighPrecision& operator+=(const HighPrecision& other);
	HighPrecision& operator-=(const HighPrecision& other);
	HighPrecision& operator*=(const HighPrecision& other);
	HighPrecision& operator*=(const int other);
	HighPrecision& operator/=(const HighPrecision& other);
	HighPrecision& operator/=(const int other);
	HighPrecision& operator%=(const HighPrecision& other);
	HighPrecision& operator%=(const int other);
	HighPrecision& operator^=(const HighPrecision& other);
	HighPrecision& operator^=(const int other);
	bool operator==(const HighPrecision& other) const;
	bool operator!=(const HighPrecision& other) const;
	bool operator<(const HighPrecision& other) const;
	bool operator<=(const HighPrecision& other) const;
	bool operator>(const HighPrecision& other) const;
	bool operator>=(const HighPrecision& other) const;
	friend std::ostream& operator<<(std::ostream& os, const HighPrecision& hp);
	friend std::istream& operator>>(std::istream& is, HighPrecision& hp);

public:
	void setValue(const std::vector<int>& newDigits);
	std::vector<int> getValue() const;
};

using HP = HighPrecision;


// 高精度浮点数类
class HighPrecisionFloat {
private:
	std::vector<int> digits; // 所有数字（整数部分+小数部分）
	int decimalPoint; // 小数点位置（从右边数起的位数）
	bool negative; // 是否为负数
	
	void normalize(); // 规范化：去除前导零和尾随零
	void alignDecimal(HighPrecisionFloat& a, HighPrecisionFloat& b) const; // 对齐小数点
	
public:
	// 构造函数
	HighPrecisionFloat(); // 默认构造函数，初始化为0
	HighPrecisionFloat(int number); // 从整数构造
	HighPrecisionFloat(double number, int precision = 10); // 从浮点数构造，precision指定精度
	HighPrecisionFloat(const std::string& numberStr); // 从字符串构造（支持 "123.456", "-0.001" 等格式）
	HighPrecisionFloat(const HighPrecisionFloat& other); // 拷贝构造函数
	HighPrecisionFloat& operator=(const HighPrecisionFloat& other); // 拷贝赋值运算符
	HighPrecisionFloat(HighPrecisionFloat&& other) noexcept; // 移动构造函数
	HighPrecisionFloat& operator=(HighPrecisionFloat&& other) noexcept; // 移动赋值运算符
	~HighPrecisionFloat();
	
	// 算术运算符
	HighPrecisionFloat operator+(const HighPrecisionFloat& other) const;
	HighPrecisionFloat operator-(const HighPrecisionFloat& other) const;
	HighPrecisionFloat operator*(const HighPrecisionFloat& other) const;
	HighPrecisionFloat operator/(const HighPrecisionFloat& other) const; // 除法，指定精度
	HighPrecisionFloat operator-() const; // 取负运算符
	
	// 复合赋值运算符
	HighPrecisionFloat& operator+=(const HighPrecisionFloat& other);
	HighPrecisionFloat& operator-=(const HighPrecisionFloat& other);
	HighPrecisionFloat& operator*=(const HighPrecisionFloat& other);
	HighPrecisionFloat& operator/=(const HighPrecisionFloat& other);
	
	// 比较运算符
	bool operator==(const HighPrecisionFloat& other) const;
	bool operator!=(const HighPrecisionFloat& other) const;
	bool operator<(const HighPrecisionFloat& other) const;
	bool operator<=(const HighPrecisionFloat& other) const;
	bool operator>(const HighPrecisionFloat& other) const;
	bool operator>=(const HighPrecisionFloat& other) const;
	
	// 输入输出运算符
	friend std::ostream& operator<<(std::ostream& os, const HighPrecisionFloat& hpf);
	friend std::istream& operator>>(std::istream& is, HighPrecisionFloat& hpf);
	
	// 工具函数
	HighPrecisionFloat abs() const; // 绝对值
	HighPrecisionFloat power(int exponent) const; // 整数次幂
	HighPrecisionFloat sqrt(int precision = 50) const; // 平方根（牛顿迭代法）
	
	// 设置精度（截断或补零小数部分）
	void setPrecision(int precision);
	int getPrecision() const; // 获取当前小数位数
	
	// 转换函数
	double toDouble() const; // 转换为 double（可能损失精度）
	std::string toString() const; // 转换为字符串
	
	// 状态检查函数
	bool isZero() const;
	bool isPositive() const;
	bool isNegative() const;
};

using HPF = HighPrecisionFloat;


#endif // !HIGH_PRECISION_H
