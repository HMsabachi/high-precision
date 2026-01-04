#include "high-precision.h"
#include "high-precision.h"
#include "high-precision.h"
#include "high-precision.h"
#include <iostream>
#include <algorithm>

HighPrecision::HighPrecision() // 默认构造函数，初始化为0
{
	digits.push_back(0);
}
HighPrecision::~HighPrecision() // 析构函数
{
	// 无需手动释放资源，vector会自动管理内存
}

HighPrecision::HighPrecision(int number) // 从整数构造高精度数
{
	if (number == 0) {
		digits.push_back(0);
	} else {
		while (number > 0) {
			digits.push_back(number % 10);
			number /= 10;
		}
	}
}

HighPrecision::HighPrecision(const std::string& numberStr) // 从字符串构造高精度数
{
	for (int i = numberStr.size() - 1; i >= 0; --i) {
		if (isdigit(numberStr[i])) {
			digits.push_back(numberStr[i] - '0');
		}
	}
	if (digits.empty()) {
		digits.push_back(0);
	}
}

HighPrecision::HighPrecision(const HighPrecision& other) // 拷贝构造函数
	: digits(other.digits)
{
}

HighPrecision& HighPrecision::operator=(const HighPrecision& other) // 拷贝赋值运算符
{
	if (this != &other) {
		digits = other.digits;
	}
	return *this;
}

HighPrecision::HighPrecision(HighPrecision&& other) noexcept // 移动构造函数
	: digits(std::move(other.digits))
{
}

HighPrecision& HighPrecision::operator=(HighPrecision&& other) noexcept // 移动赋值运算符
{
	if (this != &other) {
		digits = std::move(other.digits);
	}
	return *this;
}

HighPrecision HighPrecision::operator+(const HighPrecision& other) const // 加法运算符
{
	HighPrecision result;
	result.digits.clear(); // 清空默认的0
	const size_t maxSize = std::max(digits.size(), other.digits.size());
	int carry = 0; // 进位
	for (size_t i = 0; i < maxSize || carry; ++i) {
		int digitSum = carry;
		if (i < digits.size()) {
			digitSum += digits[i];
		}
		if (i < other.digits.size()) {
			digitSum += other.digits[i];
		}
		result.digits.push_back(digitSum % 10); // 当前位
		carry = digitSum / 10; // 更新进位
	}
	return result;
}

HighPrecision HighPrecision::operator-(const HighPrecision& other) const // 减法运算符
{
	HighPrecision result;
	result.digits.clear();
	const size_t maxSize = std::max(digits.size(), other.digits.size());
	int borrow = 0;
	for (size_t i = 0; i < maxSize; ++i) {
		int digitDiff = borrow;
		if (i < digits.size()) {
			digitDiff += digits[i];
		}
		if (i < other.digits.size()) {
			digitDiff -= other.digits[i];
		}
		if (digitDiff < 0) {
			digitDiff += 10;
			borrow = -1;
		} else {
			borrow = 0;
		}
		result.digits.push_back(digitDiff);
	}
	while (result.digits.size() > 1 && result.digits.back() == 0) {
		result.digits.pop_back();
	}
	return result;
}

HighPrecision HighPrecision::operator*(const HighPrecision& other) const // 乘法运算符
{
	HighPrecision result;
	result.digits.clear();
	result.digits.resize(digits.size() + other.digits.size(), 0);
	
	for (size_t i = 0; i < digits.size(); ++i) {
		int carry = 0;
		for (size_t j = 0; j < other.digits.size() || carry; ++j) {
			if (i + j >= result.digits.size()) {
				result.digits.push_back(0);
			}
			long long current = result.digits[i + j] + carry;
			if (j < other.digits.size()) {
				current += static_cast<long long>(digits[i]) * other.digits[j];
			}
			result.digits[i + j] = current % 10;
			carry = current / 10;
		}
	}
	
	while (result.digits.size() > 1 && result.digits.back() == 0) {
		result.digits.pop_back();
	}
	return result;
}

HighPrecision HighPrecision::operator*(const int other) const // 乘以整数
{
	HighPrecision result;
	result.digits.clear();
	
	if (other == 0) {
		result.digits.push_back(0);
		return result;
	}
	
	int carry = 0;
	for (size_t i = 0; i < digits.size() || carry; ++i) {
		long long current = carry;
		if (i < digits.size()) {
			current += static_cast<long long>(digits[i]) * other;
		}
		result.digits.push_back(current % 10);
		carry = current / 10;
	}
	
	return result;
}

HighPrecision HighPrecision::operator/(const HighPrecision& other) const // 除法运算符
{
	if (other == HighPrecision(0)) {
		throw std::invalid_argument("Division by zero");
	}
	
	if (*this < other) {
		return HighPrecision(0);
	}
	
	HighPrecision result;
	result.digits.clear();
	
	HighPrecision current;
	current.digits.clear();
	
	for (int i = digits.size() - 1; i >= 0; --i) {
		current.digits.insert(current.digits.begin(), digits[i]);
		while (current.digits.size() > 1 && current.digits.back() == 0) {
			current.digits.pop_back();
		}
		
		int quotient = 0;
		while (current >= other) {
			current -= other;
			++quotient;
		}
		result.digits.insert(result.digits.begin(), quotient);
	}
	
	while (result.digits.size() > 1 && result.digits.back() == 0) {
		result.digits.pop_back();
	}
	
	return result;
}

HighPrecision HighPrecision::operator/(const int other) const // 除以整数
{
	if (other == 0) {
		throw std::invalid_argument("Division by zero");
	}
	
	HighPrecision result;
	result.digits.clear();
	
	long long carry = 0;
	for (int i = digits.size() - 1; i >= 0; --i) {
		long long current = carry * 10 + digits[i];
		result.digits.insert(result.digits.begin(), current / other);
		carry = current % other;
	}
	
	while (result.digits.size() > 1 && result.digits.back() == 0) {
		result.digits.pop_back();
	}
	
	return result;
}

HighPrecision HighPrecision::operator%(const HighPrecision& other) const // 取模运算符
{
	if (other == HighPrecision(0)) {
		throw std::invalid_argument("Modulo by zero");
	}
	
	HighPrecision quotient = *this / other;
	return *this - (quotient * other);
}

HighPrecision HighPrecision::operator%(const int other) const // 对整数取模
{
	if (other == 0) {
		throw std::invalid_argument("Modulo by zero");
	}
	
	long long remainder = 0;
	for (int i = digits.size() - 1; i >= 0; --i) {
		remainder = (remainder * 10 + digits[i]) % other;
	}
	
	return HighPrecision(static_cast<int>(remainder));
}

HighPrecision HighPrecision::operator^(const HighPrecision& other) const
{
	// 幂运算符（仅支持非负整数幂）
	if (other < HighPrecision(0)) {
		throw std::invalid_argument("Negative exponent not supported");
	}
	
	HighPrecision result(1);
	HighPrecision base = *this;
	HighPrecision exponent = other;
	
	while (!exponent.digits.empty() && !(exponent.digits.size() == 1 && exponent.digits[0] == 0)) {
		if ((exponent.digits[0] & 1) == 1) { // 检查最低位是否为奇数（位运算更快）
			result = result * base;
		}
		base = base * base;
		
		int carry = 0;
		for (int i = exponent.digits.size() - 1; i >= 0; --i) {
			int current = carry * 10 + exponent.digits[i];
			exponent.digits[i] = current / 2;
			carry = current % 2;
		}
		while (exponent.digits.size() > 1 && exponent.digits.back() == 0) {
			exponent.digits.pop_back();
		}
	}
	
	return result;
}

HighPrecision HighPrecision::operator^(const int other) const // 
{
	// 幂运算符（仅支持非负整数幂）
	if (other < 0) {
		throw std::invalid_argument("Negative exponent not supported");
	}
	
	HighPrecision result(1);
	HighPrecision base = *this;
	int exponent = other;
	
	while (exponent > 0) {
		if (exponent & 1) { // 奇数
			result = result * base;
		}
		base = base * base;
		exponent >>= 1;
	}
	
	return result;
}

HighPrecision& HighPrecision::operator+=(const HighPrecision& other) // 加法赋值
{
	*this = *this + other;
	return *this;
}

HighPrecision& HighPrecision::operator-=(const HighPrecision& other) // 减法赋值
{
	*this = *this - other;
	return *this;
}

HighPrecision& HighPrecision::operator*=(const HighPrecision& other) // 乘法赋值
{
	*this = *this * other;
	return *this;
}

HighPrecision& HighPrecision::operator*=(const int other) // 乘以整数赋值
{
	*this = *this * other;
	return *this;
}

HighPrecision& HighPrecision::operator/=(const HighPrecision& other) // 除法赋值
{
	*this = *this / other;
	return *this;
}

HighPrecision& HighPrecision::operator/=(const int other) // 除以整数赋值
{
	*this = *this / other;
	return *this;
}

HighPrecision& HighPrecision::operator%=(const HighPrecision& other) // 取模赋值
{
	*this = *this % other;
	return *this;
}

HighPrecision& HighPrecision::operator%=(const int other) // 对整数取模赋值
{
	*this = *this % other;
	return *this;
}

HighPrecision& HighPrecision::operator^=(const HighPrecision& other)
{
	*this = *this ^ other;
	return *this;
}

HighPrecision& HighPrecision::operator^=(const int other)
{
	*this = *this ^ other;
	return *this;
}

bool HighPrecision::operator==(const HighPrecision& other) const // 相等比较
{
	return digits == other.digits;
}

bool HighPrecision::operator!=(const HighPrecision& other) const // 不等比较
{
	return !(*this == other);
}

bool HighPrecision::operator<(const HighPrecision& other) const // 小于比较
{
	if (digits.size() != other.digits.size()) {
		return digits.size() < other.digits.size();
	}
	
	for (int i = digits.size() - 1; i >= 0; --i) {
		if (digits[i] != other.digits[i]) {
			return digits[i] < other.digits[i];
		}
	}
	
	return false;
}

bool HighPrecision::operator<=(const HighPrecision& other) const // 小于等于比较
{
	return *this < other || *this == other;
}

bool HighPrecision::operator>(const HighPrecision& other) const // 大于比较
{
	return !(*this <= other);
}

bool HighPrecision::operator>=(const HighPrecision& other) const // 大于等于比较
{
	return !(*this < other);
}

std::ostream& operator<<(std::ostream& os, const HighPrecision& hp) // 输出流运算符
{
	for (int i = hp.digits.size() - 1; i >= 0; --i) {
		os << hp.digits[i];
	}
	return os;
}

std::istream& operator>>(std::istream& is, HighPrecision& hp) // 输入流运算符
{
	std::string str;
	is >> str;
	hp = HighPrecision(str);
	return is;
}

void HighPrecision::setValue(const std::vector<int>& newDigits) // 设置值
{
	digits = newDigits;
	if (digits.empty()) {
		digits.push_back(0);
	}
	while (digits.size() > 1 && digits.back() == 0) {
		digits.pop_back();
	}
}

std::vector<int> HighPrecision::getValue() const // 获取值
{
	return digits;
}


// ============================================================================
// HighPrecisionFloat 实现
// ============================================================================

// 辅助函数：规范化数字（去除前导零和尾随零）
void HighPrecisionFloat::normalize() {
	// 去除尾随零（小数部分末尾的0）
	while (decimalPoint > 0 && !digits.empty() && digits[0] == 0) {
		digits.erase(digits.begin());
		--decimalPoint;
	}
	
	// 去除前导零（整数部分前面的0）
	while (digits.size() > static_cast<size_t>(decimalPoint) + 1 && digits.back() == 0) {
		digits.pop_back();
	}
	
	// 如果所有数字都是0
	if (digits.empty() || (digits.size() == 1 && digits[0] == 0)) {
		digits.clear();
		digits.push_back(0);
		decimalPoint = 0;
		negative = false;
	}
}

// 对齐两个数的小数点
void HighPrecisionFloat::alignDecimal(HighPrecisionFloat& a, HighPrecisionFloat& b) const {
	int maxDecimal = std::max(a.decimalPoint, b.decimalPoint);
	
	// 补零对齐小数部分
	while (a.decimalPoint < maxDecimal) {
		a.digits.insert(a.digits.begin(), 0);
		++a.decimalPoint;
	}
	while (b.decimalPoint < maxDecimal) {
		b.digits.insert(b.digits.begin(), 0);
		++b.decimalPoint;
	}
}

// 构造函数
HighPrecisionFloat::HighPrecisionFloat() : decimalPoint(0), negative(false) {
	digits.push_back(0);
}

HighPrecisionFloat::HighPrecisionFloat(int number) : decimalPoint(0), negative(number < 0) {
	if (number == 0) {
		digits.push_back(0);
	} else {
		number = std::abs(number);
		while (number > 0) {
			digits.push_back(number % 10);
			number /= 10;
		}
		std::reverse(digits.begin(), digits.end());
	}
}

HighPrecisionFloat::HighPrecisionFloat(double number, int precision) : decimalPoint(0), negative(number < 0) {
	number = std::abs(number);
	
	// 分离整数和小数部分
	long long intPart = static_cast<long long>(number);
	double fracPart = number - intPart;
	
	// 处理整数部分
	if (intPart == 0) {
		digits.push_back(0);
	} else {
		while (intPart > 0) {
			digits.push_back(intPart % 10);
			intPart /= 10;
		}
		std::reverse(digits.begin(), digits.end());
	}
	
	// 处理小数部分
	for (int i = 0; i < precision; ++i) {
		fracPart *= 10;
		int digit = static_cast<int>(fracPart);
		digits.insert(digits.begin(), digit);
		fracPart -= digit;
		++decimalPoint;
	}
	
	normalize();
}

HighPrecisionFloat::HighPrecisionFloat(const std::string& numberStr) : decimalPoint(0), negative(false) {
	if (numberStr.empty()) {
		digits.push_back(0);
		return;
	}
	
	size_t start = 0;
	if (numberStr[0] == '-') {
		negative = true;
		start = 1;
	} else if (numberStr[0] == '+') {
		start = 1;
	}
	
	int dotPos = -1;
	for (size_t i = start; i < numberStr.size(); ++i) {
		if (numberStr[i] == '.') {
			dotPos = i;
			break;
		}
	}
	
	// 没有小数点
	if (dotPos == -1) {
		for (size_t i = start; i < numberStr.size(); ++i) {
			if (isdigit(numberStr[i])) {
				digits.push_back(numberStr[i] - '0');
			}
		}
	} else {
		// 整数部分
		for (size_t i = start; i < static_cast<size_t>(dotPos); ++i) {
			if (isdigit(numberStr[i])) {
				digits.push_back(numberStr[i] - '0');
			}
		}
		// 小数部分（逆序存储）
		for (size_t i = numberStr.size() - 1; i > static_cast<size_t>(dotPos); --i) {
			if (isdigit(numberStr[i])) {
				digits.insert(digits.begin(), numberStr[i] - '0');
				++decimalPoint;
			}
		}
	}
	
	if (digits.empty()) {
		digits.push_back(0);
	}
	
	normalize();
}

HighPrecisionFloat::HighPrecisionFloat(const HighPrecisionFloat& other)
	: digits(other.digits), decimalPoint(other.decimalPoint), negative(other.negative) {
}

HighPrecisionFloat& HighPrecisionFloat::operator=(const HighPrecisionFloat& other) {
	if (this != &other) {
		digits = other.digits;
		decimalPoint = other.decimalPoint;
		negative = other.negative;
	}
	return *this;
}

HighPrecisionFloat::HighPrecisionFloat(HighPrecisionFloat&& other) noexcept
	: digits(std::move(other.digits)), decimalPoint(other.decimalPoint), negative(other.negative) {
}

HighPrecisionFloat& HighPrecisionFloat::operator=(HighPrecisionFloat&& other) noexcept {
	if (this != &other) {
		digits = std::move(other.digits);
		decimalPoint = other.decimalPoint;
		negative = other.negative;
	}
	return *this;
}

HighPrecisionFloat::~HighPrecisionFloat() {
}

// 加法运算符
HighPrecisionFloat HighPrecisionFloat::operator+(const HighPrecisionFloat& other) const {
	if (negative != other.negative) {
		if (negative) {
			return other - (-(*this));
		} else {
			return *this - (-other);
		}
	}
	
	HighPrecisionFloat a = *this;
	HighPrecisionFloat b = other;
	alignDecimal(a, b);
	
	HighPrecisionFloat result;
	result.digits.clear();
	result.decimalPoint = a.decimalPoint;
	result.negative = a.negative;
	
	int carry = 0;
	size_t maxSize = std::max(a.digits.size(), b.digits.size());
	
	// 从最低位（索引0）开始相加
	for (size_t i = 0; i < maxSize || carry; ++i) {
		int sum = carry;
		if (i < a.digits.size()) sum += a.digits[i];
		if (i < b.digits.size()) sum += b.digits[i];
		
		result.digits.push_back(sum % 10);  // 从低位向高位添加
		carry = sum / 10;
	}
	
	result.normalize();
	return result;
}

// 减法运算符
HighPrecisionFloat HighPrecisionFloat::operator-(const HighPrecisionFloat& other) const {
	if (negative != other.negative) {
		if (negative) {
			return -((-(*this)) + other);
		} else {
			return *this + (-other);
		}
	}
	
	HighPrecisionFloat a = *this;
	HighPrecisionFloat b = other;
	alignDecimal(a, b);
	
	// 确保 a >= b（绝对值）
	bool resultNegative = false;
	if (a.digits.size() < b.digits.size() || 
		(a.digits.size() == b.digits.size() && a.digits < b.digits)) {
		std::swap(a, b);
		resultNegative = !a.negative;
	} else {
		resultNegative = a.negative;
	}
	
	HighPrecisionFloat result;
	result.digits.clear();
	result.decimalPoint = a.decimalPoint;
	result.negative = resultNegative;
	
	int borrow = 0;
	// 从最低位（索引0）开始相减
	for (size_t i = 0; i < a.digits.size(); ++i) {
		int diff = borrow + a.digits[i];
		if (i < b.digits.size()) diff -= b.digits[i];
		
		if (diff < 0) {
			diff += 10;
			borrow = -1;
		} else {
			borrow = 0;
		}
		result.digits.push_back(diff);  // 从低位向高位添加
	}
	
	result.normalize();
	return result;
}

// 乘法运算符
HighPrecisionFloat HighPrecisionFloat::operator*(const HighPrecisionFloat& other) const {
	HighPrecisionFloat result;
	result.digits.clear();
	result.decimalPoint = this->decimalPoint + other.decimalPoint;
	result.negative = (this->negative != other.negative);
	
	// 初始化结果数组
	result.digits.resize(this->digits.size() + other.digits.size(), 0);
	
	// 乘法运算（从低位到高位）
	for (size_t i = 0; i < this->digits.size(); ++i) {
		int carry = 0;
		for (size_t j = 0; j < other.digits.size() || carry; ++j) {
			if (i + j >= result.digits.size()) {
				result.digits.push_back(0);
			}
			long long current = result.digits[i + j] + carry;
			if (j < other.digits.size()) {
				current += static_cast<long long>(this->digits[i]) * other.digits[j];
			}
			result.digits[i + j] = current % 10;
			carry = current / 10;
		}
	}
	
	result.normalize();
	return result;
}

// 除法运算符
HighPrecisionFloat HighPrecisionFloat::operator/(const HighPrecisionFloat& other) const {
	if (other.isZero()) {
		throw std::invalid_argument("Division by zero");
	}
	
	const int DIVISION_PRECISION = 50; // 除法精度
	
	HighPrecisionFloat result;
	result.digits.clear();
	result.negative = (this->negative != other.negative);
	
	// 移除小数点，转换为整数除法
	HighPrecisionFloat dividend = this->abs();
	HighPrecisionFloat divisor = other.abs();
	
	// 调整小数点位置
	int adjustedDecimalPoint = this->decimalPoint - other.decimalPoint + DIVISION_PRECISION;
	
	// 将被除数扩大以保证精度
	for (int i = 0; i < DIVISION_PRECISION; ++i) {
		dividend.digits.insert(dividend.digits.begin(), 0);
		++dividend.decimalPoint;
	}
	
	result.decimalPoint = adjustedDecimalPoint;
	
	// 执行长除法
	HighPrecisionFloat current;
	current.digits.clear();
	current.decimalPoint = 0;
	current.negative = false;
	
	// 从高位到低位处理
	for (int i = dividend.digits.size() - 1; i >= 0; --i) {
		// 将下一位数字添加到当前余数
		current.digits.insert(current.digits.begin(), dividend.digits[i]);
		current.normalize();
		
		// 计算当前位的商
		int quotient = 0;
		while (current >= divisor) {
			current = current - divisor;
			++quotient;
		}
		result.digits.insert(result.digits.begin(), quotient);
	}
	
	// 确保结果不为空
	if (result.digits.empty()) {
		result.digits.push_back(0);
	}
	
	result.normalize();
	return result;
}

// 取负运算符
HighPrecisionFloat HighPrecisionFloat::operator-() const {
	HighPrecisionFloat result = *this;
	if (!result.isZero()) {
		result.negative = !result.negative;
	}
	return result;
}

// 复合赋值运算符
HighPrecisionFloat& HighPrecisionFloat::operator+=(const HighPrecisionFloat& other) {
	*this = *this + other;
	return *this;
}

HighPrecisionFloat& HighPrecisionFloat::operator-=(const HighPrecisionFloat& other) {
	*this = *this - other;
	return *this;
}

HighPrecisionFloat& HighPrecisionFloat::operator*=(const HighPrecisionFloat& other) {
	*this = *this * other;
	return *this;
}

HighPrecisionFloat& HighPrecisionFloat::operator/=(const HighPrecisionFloat& other) {
	*this = *this / other;
	return *this;
}

// 比较运算符
bool HighPrecisionFloat::operator==(const HighPrecisionFloat& other) const {
	if (negative != other.negative) return false;
	if (decimalPoint != other.decimalPoint) return false;
	return digits == other.digits;
}

bool HighPrecisionFloat::operator!=(const HighPrecisionFloat& other) const {
	return !(*this == other);
}

bool HighPrecisionFloat::operator<(const HighPrecisionFloat& other) const {
	if (negative != other.negative) {
		return negative;
	}
	
	HighPrecisionFloat a = *this;
	HighPrecisionFloat b = other;
	alignDecimal(a, b);
	
	if (a.digits.size() != b.digits.size()) {
		return negative ? (a.digits.size() > b.digits.size()) : (a.digits.size() < b.digits.size());
	}
	
	for (int i = a.digits.size() - 1; i >= 0; --i) {
		if (a.digits[i] != b.digits[i]) {
			return negative ? (a.digits[i] > b.digits[i]) : (a.digits[i] < b.digits[i]);
		}
	}
	
	return false;
}

bool HighPrecisionFloat::operator<=(const HighPrecisionFloat& other) const {
	return *this < other || *this == other;
}

bool HighPrecisionFloat::operator>(const HighPrecisionFloat& other) const {
	return !(*this <= other);
}

bool HighPrecisionFloat::operator>=(const HighPrecisionFloat& other) const {
	return !(*this < other);
}

// 输入输出运算符
std::ostream& operator<<(std::ostream& os, const HighPrecisionFloat& hpf) {
	if (hpf.negative) {
		os << '-';
	}
	
	if (hpf.digits.size() <= static_cast<size_t>(hpf.decimalPoint)) {
		os << "0.";
		for (int i = 0; i < hpf.decimalPoint - static_cast<int>(hpf.digits.size()); ++i) {
			os << '0';
		}
		for (size_t i = hpf.digits.size(); i > 0; --i) {
			os << hpf.digits[i - 1];
		}
	} else {
		for (size_t i = hpf.digits.size(); i > static_cast<size_t>(hpf.decimalPoint); --i) {
			os << hpf.digits[i - 1];
		}
		if (hpf.decimalPoint > 0) {
			os << '.';
			for (int i = hpf.decimalPoint - 1; i >= 0; --i) {
				os << hpf.digits[i];
			}
		}
	}
	
	return os;
}

std::istream& operator>>(std::istream& is, HighPrecisionFloat& hpf) {
	std::string str;
	is >> str;
	hpf = HighPrecisionFloat(str);
	return is;
}

// 工具函数
HighPrecisionFloat HighPrecisionFloat::abs() const {
	HighPrecisionFloat result = *this;
	result.negative = false;
	return result;
}

HighPrecisionFloat HighPrecisionFloat::power(int exponent) const {
	if (exponent < 0) {
		return HighPrecisionFloat(1) / this->power(-exponent);
	}
	if (exponent == 0) {
		return HighPrecisionFloat(1);
	}
	if (exponent == 1) {
		return *this;
	}
	
	HighPrecisionFloat result(1);
	HighPrecisionFloat base = *this;
	
	while (exponent > 0) {
		if (exponent & 1) {
			result = result * base;
		}
		base = base * base;
		exponent >>= 1;
	}
	
	return result;
}

HighPrecisionFloat HighPrecisionFloat::sqrt(int precision) const {
	if (negative) {
		throw std::invalid_argument("Cannot compute square root of negative number");
	}
	if (isZero()) {
		return HighPrecisionFloat(0);
	}
	
	// 牛顿迭代法：x_(n+1) = (x_n + a/x_n) / 2
	HighPrecisionFloat x = *this;
	HighPrecisionFloat two(2);
	
	for (int i = 0; i < precision; ++i) {
		x = (x + (*this / x)) / two;
	}
	
	return x;
}

void HighPrecisionFloat::setPrecision(int precision) {
	if (precision < 0) precision = 0;
	
	while (decimalPoint > precision) {
		if (!digits.empty()) {
			digits.erase(digits.begin());
		}
		--decimalPoint;
	}
	
	while (decimalPoint < precision) {
		digits.insert(digits.begin(), 0);
		++decimalPoint;
	}
	
	normalize();
}

int HighPrecisionFloat::getPrecision() const {
	return decimalPoint;
}

double HighPrecisionFloat::toDouble() const {
	double result = 0.0;
	double multiplier = 1.0;
	
	for (int i = decimalPoint - 1; i >= 0; --i) {
		result += digits[i] * multiplier;
		multiplier *= 10.0;
	}
	
	multiplier = 0.1;
	for (size_t i = decimalPoint; i < digits.size(); ++i) {
		result += digits[i] * multiplier;
		multiplier *= 0.1;
	}
	
	return negative ? -result : result;
}

std::string HighPrecisionFloat::toString() const {
	std::string result;
	if (negative) {
		result += '-';
	}
	
	if (digits.size() <= static_cast<size_t>(decimalPoint)) {
		result += "0.";
		for (int i = 0; i < decimalPoint - static_cast<int>(digits.size()); ++i) {
			result += '0';
		}
		for (int i = digits.size() - 1; i >= 0; --i) {
			result += ('0' + digits[i]);
		}
	} else {
		for (int i = digits.size() - 1; i >= decimalPoint; --i) {
			result += ('0' + digits[i]);
		}
		if (decimalPoint > 0) {
			result += '.';
			for (int i = decimalPoint - 1; i >= 0; --i) {
				result += ('0' + digits[i]);
			}
		}
	}
	
	return result;
}

bool HighPrecisionFloat::isZero() const {
	return digits.size() == 1 && digits[0] == 0;
}

bool HighPrecisionFloat::isPositive() const {
	return !negative && !isZero();
}

bool HighPrecisionFloat::isNegative() const {
	return negative && !isZero();
}









