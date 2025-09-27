#include <iostream>
#include <limits> // 包含numeric_limits头文件

struct inflatable   // structure definition
{
    char name[20];
    float volume;
    double price;
};

int main()
{
    using namespace std;
    inflatable * ps = new inflatable; // allot memory for structure
    cout << "Enter name of inflatable item: ";
    cin.get(ps->name, 20);            // 从输入流中读取最多 19 个字符
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清除输入流中的换行符和剩余内容
    cout << "Enter volume in cubic feet: ";
    while (!(cin >> ps->volume)) {     // 如果输入不是有效的浮点数，则循环直到读取成功
        cin.clear();                    // 清除错误标志
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清除输入流中的换行符和剩余内容
        cout << "Invalid input. Please try again.\n";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清除输入流中的换行符和剩余内容
    cout << "Enter price: $";
    while (!(cin >> ps->price)) {     // 如果输入不是有效的浮点数，则循环直到读取成功
        cin.clear();                    // 清除错误标志
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清除输入流中的换行符和剩余内容
        cout << "Invalid input. Please try again.\n";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清除输入流中的换行符和剩余内容
    cout << "Name: " << ps->name << endl;              // method 2
    cout << "Volume: " << ps->volume << " cubic feet\n"; // method 1
    cout << "Price: $" << ps->price << endl;             // method 1
    delete ps;                        // free memory used by structure

    return 0;
}
