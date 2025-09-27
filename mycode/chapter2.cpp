#include <iostream> // 头文件
#include <cmath>

using namespace std;    //名称空间（区分不同版本，使用后可以省略编译指令，如std:cout）
/*只使用需要的名称
* using std::cin;
using std::out;
using std::endl;
using std::cin;
*/
void test_cinandcout(void) {
    int carrots;
    cin >> carrots;
    cout << "I have " << carrots << " carrots." << endl; //输出＋换行
}

void test_cmath() {
    int area = 16;
    double slide = sqrt(area);
    double answer = pow(area, 2);
    cout << "area: " << area << "; " << "slide: " << slide << endl;
    cout << "pow: " << answer << endl;
}

int main()
{
    //test_cinandcout();
    test_cmath();
}

