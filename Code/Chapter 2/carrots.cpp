// carrots.cpp -- food processing program
// uses and displays a variable

#include <iostream>

int main()
{
    using namespace std;
    
    int carrots;            // declare an integer variable 声明一个整数变量
    
    carrots = 25;            // assign a value to the variable 为变量赋值
    cout << "I have ";
    cout << carrots;        // display the value of the variable 显示变量的值
    cout << " carrots.";
    cout << endl;
    carrots = carrots - 1;  // modify the variable 修改变量
    cout << "Crunch, crunch. Now I have " << carrots << " carrots." << endl;
    // cin.get();
	return 0;
}
