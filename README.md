# High Precision Library (高精度数学库)

一个强大的C++高精度数学运算库，支持任意精度的整数和浮点数运算。

## 特性

- **高精度整数运算**：支持任意大小的整数计算
- **高精度浮点运算**：支持任意精度的浮点数计算
- **完整的运算符重载**：支持 +, -, *, /, %, ^ 等运算符
- **比较运算**：支持所有比较运算符
- **易于使用**：类似于内置类型的使用方式
- **高效实现**：优化的算法确保性能

## 项目结构

```
high-precision/
├── CMakeLists.txt          # CMake 构建配置文件
├── README.md               # 项目说明文档
├── high-precision.h        # 头文件
├── high-precision.cpp      # 实现文件
└── example/
    └── example.cpp         # 示例代码
```

## 编译与安装

### 使用 CMake 构建

```bash
# 创建构建目录
mkdir build
cd build

# 配置项目
cmake ..

# 编译
cmake --build .

# 运行示例
./bin/example  # Linux/Mac
# 或
.\bin\example.exe  # Windows
```

### 使用 Visual Studio (Windows)

1. 使用 Visual Studio 打开项目文件夹
2. Visual Studio 会自动识别 CMakeLists.txt
3. 选择"生成" -> "全部生成"
4. 运行示例程序

## 快速开始

### 高精度整数 (HighPrecision / HP)

```cpp
#include "high-precision.h"
#include <iostream>

int main() {
    // 创建高精度整数
    HP a(123456789);
    HP b("987654321");
    
    // 基本运算
    HP sum = a + b;
    HP diff = b - a;
    HP product = a * b;
    HP quotient = b / a;
    HP remainder = b % a;
    
    // 幂运算
    HP power = a ^ 10;
    
    // 输出结果
    std::cout << "a + b = " << sum << std::endl;
    std::cout << "a ^ 10 = " << power << std::endl;
    
    return 0;
}
```

### 高精度浮点数 (HighPrecisionFloat / HPF)

```cpp
#include "high-precision.h"
#include <iostream>

int main() {
    // 创建高精度浮点数
    HPF x(3.14159265358979323846);
    HPF y("2.71828182845904523536");
    
    // 基本运算
    HPF sum = x + y;
    HPF product = x * y;
    HPF quotient = x / y;
    
    // 数学函数
    HPF squared = x.power(2);
    HPF root = HPF(2).sqrt(50);
    HPF absolute = (-x).abs();
    
    // 输出结果
    std::cout << "x + y = " << sum << std::endl;
    std::cout << "sqrt(2) = " << root << std::endl;
    
    return 0;
}
```

## API 文档

### HighPrecision 类 (整数高精度)

#### 构造函数
- `HighPrecision()` - 默认构造，初始化为 0
- `HighPrecision(int number)` - 从整数构造
- `HighPrecision(const std::string& numberStr)` - 从字符串构造

#### 运算符
- **算术运算**: `+`, `-`, `*`, `/`, `%`, `^` (幂运算)
- **复合赋值**: `+=`, `-=`, `*=`, `/=`, `%=`, `^=`
- **比较运算**: `==`, `!=`, `<`, `<=`, `>`, `>=`
- **输入输出**: `<<`, `>>`

#### 成员函数
- `void setValue(const std::vector<int>& newDigits)` - 设置值
- `std::vector<int> getValue() const` - 获取内部数组

### HighPrecisionFloat 类 (浮点高精度)

#### 构造函数
- `HighPrecisionFloat()` - 默认构造，初始化为 0
- `HighPrecisionFloat(int number)` - 从整数构造
- `HighPrecisionFloat(double number, int precision = 10)` - 从浮点数构造
- `HighPrecisionFloat(const std::string& numberStr)` - 从字符串构造

#### 运算符
- **算术运算**: `+`, `-`, `*`, `/`, `-` (取负)
- **复合赋值**: `+=`, `-=`, `*=`, `/=`
- **比较运算**: `==`, `!=`, `<`, `<=`, `>`, `>=`
- **输入输出**: `<<`, `>>`

#### 成员函数
- `HighPrecisionFloat abs() const` - 绝对值
- `HighPrecisionFloat power(int exponent) const` - 整数次幂
- `HighPrecisionFloat sqrt(int precision = 50) const` - 平方根（牛顿迭代法）
- `void setPrecision(int precision)` - 设置精度
- `int getPrecision() const` - 获取当前精度
- `double toDouble() const` - 转换为 double
- `std::string toString() const` - 转换为字符串
- `bool isZero() const` - 是否为零
- `bool isPositive() const` - 是否为正数
- `bool isNegative() const` - 是否为负数


## 注意事项

1. 高精度运算相比内置类型会慢很多，只在必要时使用
2. 浮点除法和平方根运算可能需要较长时间
3. 幂运算仅支持非负整数指数（整数类）
4. 除零操作会抛出 `std::invalid_argument` 异常

## 性能优化建议

- 使用 `*=`, `+=` 等复合赋值运算符而不是 `=` `+` 运算符
- 对于大量计算，考虑使用引用传递参数
- 整数运算时，优先使用 `int` 版本的运算符（如 `* int`, `/ int`）

## 编译要求

- C++11 或更高版本
- CMake 3.10 或更高版本
- 支持的编译器：GCC, Clang, MSVC

## 类型别名

为了方便使用，库提供了以下类型别名：
- `using HP = HighPrecision;`
- `using HPF = HighPrecisionFloat;`

## 许可证

本项目采用 MIT 许可证。

## 贡献

欢迎提交 Issue 和 Pull Request！

## 作者

HMsabachi

## 版本历史

- **v1.0.0** - 初始版本
  - 实现高精度整数类
  - 实现高精度浮点数类
  - 支持基本算术运算
  - 支持数学函数（幂、平方根）
