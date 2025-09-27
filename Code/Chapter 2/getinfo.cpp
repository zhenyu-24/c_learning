// getinfo.cpp -- input and output
#include <iostream>

int main()
{
    using namespace std;
    
    int carrots;
    
    cout << "How many carrots do you have?" << endl;
    cin >> carrots;                // C++ input
    cout << "Here are two more. ";
    carrots = carrots + 2;
// the next line concatenates output 下一行连接输出
    cout << "Now you have " << carrots << " carrots." << endl;
	// cin.get();
	// cin.get();
    return 0;
}
