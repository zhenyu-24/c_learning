// hexoct2.cpp -- display values in hex and octal
#include <iostream> // 控制符dec, hex, oct
using namespace std;
int main()
{
    using namespace std;
    int chest = 42;
    int waist = 42; 
    int inseam = 42;

    cout << "Monsieur cuts a striking figure!"  << endl;
    cout << "chest = " << chest << " (decimal for 42)" << endl;
    cout << hex;      // manipulator for changing number base，使用16进制
    cout << "waist = " << waist << " (hexadecimal for 42)" << endl;
    cout << oct;      // manipulator for changing number base
    cout << "inseam = " << inseam << " (octal for 42)" << endl;
    // cin.get();
    return 0; 
}
