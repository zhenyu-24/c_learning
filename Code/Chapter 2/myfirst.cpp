// P11
#include <iostream>                           // a PREPROCESSOR directive
int main()                                    // 函数头
{                                             // 函数体的开始
    using namespace std;                      // 使定义可见
    cout << "Come up and C++ me some time.";  // message
    cout << endl;                             // 开始新行
    cout << "You won't regret it!" << endl;   // more output
//如果输出窗口在您可以读取之前关闭，
//添加以下代码：
     cout << "Press any key to continue." <<endl;
	 cin.get();
    return 0;                                 // 结束 main()
}                                             // 函数体结束
