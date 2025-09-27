#include <iostream>
#include <climits>              // use limits.h for older systems,包含关于整型限制的信息
#include <iomanip>              // 用于设置精度
#include <typeinfo>            // 用于变量类型信息

#define ZERO 0      //定义符号常量

using namespace std;

void test_limits() {
    int n_int = INT_MAX;        // INT_MAX 最大值
    short n_short = SHRT_MAX;   // SHRT_MAX 最大值
    long n_long = LONG_MAX;
    long long n_llong = LLONG_MAX;

    // sizeof operator 输出类型在当前系统中占用的字节数
    /*
    带括号的形式 ：sizeof(type)
    用于计算数据类型的大小。
    不带括号的形式 ：sizeof expression
    用于计算表达式或变量的大小。
    */
    cout << "int is " << sizeof(int) << " bytes." << endl;
    cout << "short is " << sizeof n_short << " bytes." << endl;
    cout << "long is " << sizeof n_long << " bytes." << endl;
    cout << "long long is " << sizeof n_llong << " bytes." << endl;
    cout << endl;

    cout << "Maximum values:" << endl;
    cout << "int: " << n_int << endl;
    cout << "short: " << n_short << endl;
    cout << "long: " << n_long << endl;
    cout << "long long: " << n_llong << endl << endl;

    cout << "Minimum int value = " << INT_MIN << endl;
    cout << "Bits per byte = " << CHAR_BIT << endl;
    // cin.get();
}

void hexoct()
{
    int chest = 42;
    int waist = 42;
    int inseam = 42;
    /*
    0x42-十六进制
    042-八进制
    */

    cout << "Monsieur cuts a striking figure!" << endl;
    cout << "chest = " << chest << " (decimal for 42)" << endl;
    cout << hex;      // 使用16进制
    cout << "waist = " << waist << " (hexadecimal for 42)" << endl;
    cout << oct;      // 使用8进制
    cout << "inseam = " << inseam << " (octal for 42)" << endl;
    // cin.get();
}

void morechar()
{
    char ch = 'M';      // 定义一个字符
    int i = ch;         // 将字符存储在int变量中
    cout << "The ASCII code for " << ch << " is " << i << endl;
    cout.put(ch);       // 使用cout.put()函数输出字符
}

void floatnum()
{
    double value = 123.456;

    // 默认输出格式
    std::cout << "Default: " << value << std::endl;

    // 设置为 fixed 格式
    std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
    std::cout << "Fixed format: " << value << std::endl;

    // 设置精度为 2 位小数
    std::cout << std::setprecision(2); // 使用 setprecision 设置小数点后位数
    std::cout << "Fixed with precision 2: " << value << std::endl;
}

void autotest()
{
    auto x = 1.3e12L;    // 自动类型设置
    auto y = 12;
    cout << typeid(x).name() << endl;
    cout << typeid(y).name() << endl;
}

int main()
{
    const int Fave = 27;        // 常量, 提到# define
    // test_limits();
    // hexoct();
    // morechar();
    // floatnum();
    autotest();
    return 0;
}
