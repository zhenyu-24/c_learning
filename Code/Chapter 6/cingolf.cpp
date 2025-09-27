#include <iostream>
#include <string>
#include <cctype>
#include <limits>

int main() {
    std::string input;
    bool validInput = false;

    while (!validInput) {
        std::cout << "请输入一个数字: ";
        std::cin >> input;

        bool isNumber = true;
        bool hasDot = false;
        for (char c : input) {
            if (c == '.' && !hasDot) {
                hasDot = true;
            }
            else if (!std::isdigit(c)) {
                isNumber = false;
                break;
            }
        }

        if (isNumber && (hasDot || !input.empty()) && input != ".") {//input.compare(".")
            validInput = true;
        }
        else {
            std::cout << "无效输入，请输入一个数字。" << std::endl;
            std::cin.clear();  // 清除错误标记
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // 忽略之前的错误输入
        }
    }

    double number = std::stod(input);//std::stod 是 C++ 标准库中的一个函数，用于将字符串转换为double。
    std::cout << "你输入的数字是: " << number << std::endl;

    return 0;
}
