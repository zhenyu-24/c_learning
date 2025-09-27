#include <iostream>
#include <climits>
#include <iomanip>
#include <typeinfo>
#include "fun3.h"

#define ZERO 0

void test_limits() {
    int n_int = INT_MAX;
    short n_short = SHRT_MAX;
    long n_long = LONG_MAX;
    long long n_llong = LLONG_MAX;

    std::cout << "int is " << sizeof(int) << " bytes." << std::endl;
    std::cout << "short is " << sizeof n_short << " bytes." << std::endl;
    std::cout << "long is " << sizeof n_long << " bytes." << std::endl;
    std::cout << "long long is " << sizeof n_llong << " bytes." << std::endl;
    std::cout << std::endl;

    std::cout << "Maximum values:" << std::endl;
    std::cout << "int: " << n_int << std::endl;
    std::cout << "short: " << n_short << std::endl;
    std::cout << "long: " << n_long << std::endl;
    std::cout << "long long: " << n_llong << std::endl << std::endl;

    std::cout << "Minimum int value = " << INT_MIN << std::endl;
    std::cout << "Bits per byte = " << CHAR_BIT << std::endl;
}

void hexoct() {
    int chest = 42;
    int waist = 42;
    int inseam = 42;

    std::cout << "Monsieur cuts a striking figure!" << std::endl;
    std::cout << "chest = " << chest << " (decimal for 42)" << std::endl;

    std::cout.setf(std::ios_base::hex, std::ios_base::basefield);
    std::cout << "waist = " << waist << " (hexadecimal for 42)" << std::endl;

    std::cout.setf(std::ios_base::oct, std::ios_base::basefield);
    std::cout << "inseam = " << inseam << " (octal for 42)" << std::endl;

    // 恢复为十进制（可选，避免影响后续输出）
    std::cout.setf(std::ios_base::dec, std::ios_base::basefield);
}

void morechar() {
    char ch = 'M';
    int i = ch;
    std::cout << "The ASCII code for " << ch << " is " << i << std::endl;
    std::cout.put(ch);
    std::cout << std::endl; // 换行更清晰
}

void floatnum() {
    double value = 123.456;

    // 默认输出
    std::cout << "Default: " << value << std::endl;

    // fixed 格式
    std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
    std::cout << "Fixed format: " << value << std::endl;

    // 设置精度为 2
    std::cout << std::setprecision(2);
    std::cout << "Fixed with precision 2: " << value << std::endl;

    // 恢复默认（可选）
    std::cout.unsetf(std::ios_base::floatfield);
    std::cout << std::setprecision(6); // 默认精度
}

void autotest() {
    auto x = 1.3e12L;
    auto y = 12;
    std::cout << typeid(x).name() << std::endl;
    std::cout << typeid(y).name() << std::endl;
}