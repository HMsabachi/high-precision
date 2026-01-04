#include "high-precision.h"
#include <iostream>
#include <iomanip>

using namespace std;

// 演示高精度整数运算
void demonstrateHighPrecision() {
    cout << "========================================" << endl;
    cout << "   高精度整数 (HighPrecision) 示例" << endl;
    cout << "========================================" << endl << endl;

    // 1. 基本构造和输出
    cout << "1. 基本构造和输出" << endl;
    HP a(123456789);
    HP b("987654321123456789");
    HP c = HP("111111111111111111");
    
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "c = " << c << endl << endl;

    // 2. 加法运算
    cout << "2. 加法运算" << endl;
    HP sum = a + b;
    cout << "a + b = " << sum << endl;
    
    HP sum2 = b + c;
    cout << "b + c = " << sum2 << endl << endl;

    // 3. 减法运算
    cout << "3. 减法运算" << endl;
    HP diff = b - a;
    cout << "b - a = " << diff << endl << endl;

    // 4. 乘法运算
    cout << "4. 乘法运算" << endl;
    HP product = a * HP(12345);
    cout << "a * 12345 = " << product << endl;
    
    HP product2 = HP(99999) * HP(99999);
    cout << "99999 * 99999 = " << product2 << endl << endl;

    // 5. 除法和取模运算
    cout << "5. 除法和取模运算" << endl;
    HP quotient = b / a;
    HP remainder = b % a;
    cout << "b / a = " << quotient << endl;
    cout << "b % a = " << remainder << endl << endl;

    // 6. 幂运算
    cout << "6. 幂运算" << endl;
    HP power1 = HP(2) ^ 10;
    cout << "2 ^ 10 = " << power1 << endl;
    
    HP power2 = HP(3) ^ 20;
    cout << "3 ^ 20 = " << power2 << endl;
    
    HP power3 = HP(10) ^ 50;
    cout << "10 ^ 50 = " << power3 << endl << endl;

    // 7. 比较运算
    cout << "7. 比较运算" << endl;
    cout << "a < b: " << (a < b ? "true" : "false") << endl;
    cout << "b > a: " << (b > a ? "true" : "false") << endl;
    cout << "a == HP(123456789): " << (a == HP(123456789) ? "true" : "false") << endl << endl;

    // 8. 复合赋值运算
    cout << "8. 复合赋值运算" << endl;
    HP num(100);
    cout << "初始值 num = " << num << endl;
    num += HP(50);
    cout << "num += 50, num = " << num << endl;
    num *= HP(2);
    cout << "num *= 2, num = " << num << endl;
    num -= HP(100);
    cout << "num -= 100, num = " << num << endl << endl;

    // 9. 计算阶乘（演示实际应用）
    cout << "9. 计算阶乘 20!" << endl;
    HP factorial(1);
    for (int i = 2; i <= 20; ++i) {
        factorial *= i;
    }
    cout << "20! = " << factorial << endl << endl;

    // 10. 计算斐波那契数列
    cout << "10. 计算斐波那契数列第50项" << endl;
    HP fib1(1), fib2(1);
    for (int i = 3; i <= 50; ++i) {
        HP temp = fib1 + fib2;
        fib1 = fib2;
        fib2 = temp;
    }
    cout << "Fibonacci(50) = " << fib2 << endl << endl;
}

// 演示高精度浮点数运算
void demonstrateHighPrecisionFloat() {
    cout << "========================================" << endl;
    cout << "  高精度浮点数 (HighPrecisionFloat) 示例" << endl;
    cout << "========================================" << endl << endl;

    // 1. 基本构造和输出
    cout << "1. 基本构造和输出" << endl;
    HPF x(3.14159);
    HPF y("2.71828");
    HPF z(-123.456);
    
    cout << "x = " << x << endl;
    cout << "y = " << y << endl;
    cout << "z = " << z << endl << endl;

    // 2. 加法和减法
    cout << "2. 加法和减法" << endl;
    HPF sum = x + y;
    HPF diff = x - y;
    cout << "x + y = " << sum << endl;
    cout << "x - y = " << diff << endl << endl;

    // 3. 乘法和除法
    cout << "3. 乘法和除法" << endl;
    HPF product = x * y;
    HPF quotient = x / y;
    cout << "x * y = " << product << endl;
    cout << "x / y = " << quotient << endl << endl;

    // 4. 取负和绝对值
    cout << "4. 取负和绝对值" << endl;
    HPF neg = -x;
    HPF abs_z = z.abs();
    cout << "-x = " << neg << endl;
    cout << "abs(z) = " << abs_z << endl << endl;

    // 5. 幂运算
    cout << "5. 幂运算" << endl;
    HPF squared = x.power(2);
    HPF cubed = HPF(2).power(3);
    cout << "x ^ 2 = " << squared << endl;
    cout << "2 ^ 3 = " << cubed << endl << endl;

    // 6. 平方根运算
    cout << "6. 平方根运算（牛顿迭代法）" << endl;
    HPF sqrt2 = HPF(2).sqrt(30);
    cout << "sqrt(2) = " << sqrt2 << endl;
    
    HPF sqrt10 = HPF(10).sqrt(30);
    cout << "sqrt(10) = " << sqrt10 << endl << endl;

    // 7. 比较运算
    cout << "7. 比较运算" << endl;
    cout << "x > y: " << (x > y ? "true" : "false") << endl;
    cout << "y < x: " << (y < x ? "true" : "false") << endl;
    cout << "z < 0: " << (z < HPF(0) ? "true" : "false") << endl << endl;

    // 8. 精度控制
    cout << "8. 精度控制" << endl;
    HPF pi(3.14159265358979323846, 15);
    cout << "pi (15位精度) = " << pi << endl;
    cout << "当前精度: " << pi.getPrecision() << endl;
    pi.setPrecision(5);
    cout << "设置为5位精度后: " << pi << endl << endl;

    // 9. 状态检查
    cout << "9. 状态检查函数" << endl;
    cout << "x 是否为零: " << (x.isZero() ? "true" : "false") << endl;
    cout << "x 是否为正数: " << (x.isPositive() ? "true" : "false") << endl;
    cout << "z 是否为负数: " << (z.isNegative() ? "true" : "false") << endl << endl;

    // 10. 类型转换
    cout << "10. 类型转换" << endl;
    cout << "x 转换为 double: " << x.toDouble() << endl;
    cout << "x 转换为 string: " << x.toString() << endl << endl;

    // 11. 复合运算示例
    cout << "11. 复合运算示例 - 计算圆的面积" << endl;
    HPF radius(5);
    HPF pi_val(3.14159265358979323846, 20);
    HPF area = pi_val * radius.power(2);
    cout << "半径 r = " << radius << endl;
    cout << "圆周率 π = " << pi_val << endl;
    cout << "圆的面积 = π * r^2 = " << area << endl << endl;

    // 12. 计算 e 的近似值（泰勒级数）
    cout << "12. 使用泰勒级数计算 e (前10项)" << endl;
    HPF e_approx(1);
    HPF factorial(1);
    for (int i = 1; i < 10; ++i) {
        factorial *= HPF(i);
        e_approx += HPF(1) / factorial;
    }
    cout << "e ≈ " << e_approx << endl << endl;
}

// 演示混合运算和实际应用
void demonstrateAdvancedUsage() {
    cout << "========================================" << endl;
    cout << "       高级应用和混合运算示例" << endl;
    cout << "========================================" << endl << endl;

    // 1. 大数计算：计算 100!
    cout << "1. 计算 100! (阶乘)" << endl;
    HP factorial(1);
    for (int i = 2; i <= 100; ++i) {
        factorial *= i;
    }
    cout << "100! = " << factorial << endl << endl;

    // 2. 卡塔兰数计算
    cout << "2. 计算第10个卡塔兰数 C(10)" << endl;
    // C(n) = (2n)! / ((n+1)! * n!)
    HP catalan_num(1);
    for (int i = 2; i <= 20; ++i) {
        catalan_num *= i;
    }
    HP divisor(1);
    for (int i = 2; i <= 11; ++i) {
        divisor *= i;
    }
    for (int i = 2; i <= 10; ++i) {
        divisor *= i;
    }
    HP catalan = catalan_num / divisor;
    cout << "Catalan(10) = " << catalan << endl << endl;

    // 3. 大数幂运算：2^100
    cout << "3. 计算 2^100" << endl;
    HP power_of_2 = HP(2) ^ 100;
    cout << "2^100 = " << power_of_2 << endl << endl;

    // 4. 高精度 π 的计算（莱布尼茨公式的前1000项）
    cout << "4. 使用莱布尼茨公式估算 π (前1000项)" << endl;
    HPF pi_approx(0);
    for (int i = 0; i < 1000; ++i) {
        HPF term = HPF(1) / HPF(2 * i + 1);
        if (i % 2 == 0) {
            pi_approx += term;
        } else {
            pi_approx -= term;
        }
    }
    pi_approx *= HPF(4);
    cout << "π ≈ " << pi_approx << endl << endl;

    // 5. 黄金比例计算
    cout << "5. 计算黄金比例 φ = (1 + sqrt(5)) / 2" << endl;
    HPF sqrt5 = HPF(5).sqrt(50);
    HPF golden_ratio = (HPF(1) + sqrt5) / HPF(2);
    cout << "φ = " << golden_ratio << endl << endl;

    // 6. 用户输入示例
    cout << "6. 用户输入示例" << endl;
    cout << "请输入两个大整数进行加法运算:" << endl;
    cout << "第一个数 (示例: 123456789): ";
    HP input1(123456789);
    cout << input1 << endl;
    
    cout << "第二个数 (示例: 987654321): ";
    HP input2(987654321);
    cout << input2 << endl;
    
    HP input_sum = input1 + input2;
    cout << "它们的和 = " << input_sum << endl << endl;
}

int main() {
    try {
        cout << endl;
        cout << "********************************************" << endl;
        cout << "*     高精度数学库 (High Precision Library)     *" << endl;
        cout << "*              使用示例程序              *" << endl;
        cout << "********************************************" << endl;
        cout << endl;

        // 演示高精度整数
        demonstrateHighPrecision();

        cout << endl;

        // 演示高精度浮点数
        demonstrateHighPrecisionFloat();

        cout << endl;

        // 演示高级应用
        demonstrateAdvancedUsage();

        cout << "============================================" << endl;
        cout << "           所有示例运行完成！" << endl;
        cout << "============================================" << endl;
        cout << endl;

    } catch (const exception& e) {
        cerr << "错误: " << e.what() << endl;
        return 1;
    }

    return 0;
}
