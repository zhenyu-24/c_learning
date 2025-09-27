## 第4章 复合类型
### 数组
#### 声明数组通用格式
```cpp
type arrayName[arraySize];
```
arraySize必须是一个常量表达式/const，且大于0。
arraySize不能是变量，但可以用**new**动态分配数组。
**sizeof**运算符用于数组名可以用来确定数组的字节数。

#### 初始化数组
```cpp
type arrayName[arraySize] = {value0, value1, ..., valueN};
```
如果初始化列表中的值少于arraySize，其他元素将被初始化为0。
```cpp
type arrayName[] = {value0, value1, ..., valueN};
```
如果省略arraySize，编译器将根据初始化列表中的值的数量来确定数组的大小。
```cpp
// 返回数组长度方法1
int length = sizeof(arrayName) / sizeof(arrayName[0]);
// 返回数组长度方法2
#include <iterator>
int length = std::size(arrayName);
```
返回数组长度的两种方法，推荐使用第二种方法。

### 字符串
#### 字符串数组
字符串是以空字符'\0'结尾的字符数组。
```cpp
char str[] = "Hello";
char str[6] = {'H', 'e', 'l', 'l', 'o', '\0'};
// 如果数组大小大于字符串长度+1，剩余元素将被初始化为'\0'
char str[10] = "Hello"; // str[5]到str[9]将被初始化为'\0'
```
#### 字符串操作
可以使用**<cstring>**头文件中的函数来操作字符串，如**strcpy()**, **strcat()**, **strlen()**等。如下：
```cpp
#include <cstring>
char str1[20] = "Hello, ";
char str2[] = "World!";
strcat(str1, str2); // str1现在是"Hello, World!"
int len = strlen(str1); // len是13，不包括空字符
char str3[20];
strcpy(str3, str1); // str3现在是"Hello, World!"
```
#### 字符串输入
cin读取字符串时遇到空格会停止，可以使用**cin.get()**或**cin.getline()**来读取包含空格的字符串。
**cin.getline()**读取一行到字符数组中，直到遇到换行符或达到指定长度为止，随后丢弃换行符以空字符代替。
```cpp
char str[100];
cin.getline(str, 100); // 读取一行，最多99个字符
```
**cin.get**会保留换行符到输入队列。
```cpp
cin.get(name, 100);
cin.get(); // 读取并丢弃换行符
cin,get(title, 100);
// 另一种方法，将2个类成员函数拼接起来
cin.get(name, 100).get();
```
空行会导致**cin.get()**和**cin.getline()**立即返回，且不修改数组内容。
当输入行超过数组大小时，**cin.get()**和**cin.getline()**会将多余的字符留在输入队列中，且不修改数组内容。
可以使用**cin.clear()**清除错误状态，使用**cin.ignore()**忽略输入队列中的多余字符。
```cpp
cin.clear(); // 清除错误状态
cin.ignore(10000, '\n'); // 忽略多余字符，直到遇到换行符
```
混合输入字符串和数字时，注意处理换行符。
```cpp
int age;
char name[50];
cout << "Enter your age: ";
cin >> age;
cin.get(); // 读取并丢弃换行符。或 (cin >> age).get();
cout << "Enter your name: ";
cin.getline(name, 50);
```

#### string类
声明与初始化
```cpp
#include <string>
std::string str1; // 空字符串
std::string str2("Hello"); // 使用C风格字符串初始化
std::string str3 = "World"; // 使用C风格字符串初始化
```
赋值、拼接、附加、返回长度
```cpp
str1 = "Hello"; // 赋值
str1 += " World"; // 拼接
str1.append("!"); // 附加
int len = str1.length(); // 返回长度
int len2 = str1.size(); // 返回长度，等同于length()
```
string类I/O
```cpp
#include <iostream>
#include <string>
std::string str;
std::cin >> str; // 读取单词，遇到空格停止
std::getline(std::cin, str); // 读取整行，包含空格
std::cout << str; // 输出字符串
```

### 结构体
使用场景：将各种信息存储到一个单元
#### 声明与初始化
```cpp
struct StructName {
    type member1;
    type member2;
    // ...
};
StructName var1; // 声明结构体变量
StructName var2 = {value1, value2}; // 初始化结构体变量
```
#### 访问成员
```cpp
var1.member1 = value; // 访问成员
int val = var1.member2; // 访问成员
```
#### 结构体数组
```cpp
StructName arr[10]; // 声明结构体数组
arr[0].member1 = value; // 访问结构体数组成员
```

### 共用体
使用场景：存储不同的数据类型，但只能同时存储其中一种类型。当数据项使用2种或多种格式时（但不同时使用），可节约内存。
#### 声明与初始化
```cpp
union UnionName {
    type member1;
    type member2;
    // ...
};

UnionName var; // 声明共用体变量
var.member1 = value; // 初始化共用体成员
```
#### 访问成员
```cpp
int val = var.member1; // 访问共用体成员
var.member2 = value; // 访问共用体成员
```

### 枚举
使用场景：**enum**用于定义一组创建符号常量的方式，可以替代const常量。可以用枚举定义switch语句的分支。
#### 声明与初始化
其中，枚举常量VALUE默认从0开始依次递增，可以手动指定某个枚举常量的值，后续枚举常量将从该值开始递增。
可以创建多个值相同的枚举常量。
```cpp
enum EnumName { VALUE1, VALUE2, VALUE3 }; // 声明枚举
enum EnumName { VALUE1 = 1, VALUE2 = 1, VALUE3 = 5, VALUE4 }; // 声明枚举
```
#### 访问枚举常量
```cpp
EnumName var; // 声明枚举变量
var = VALUE1; // 访问枚举常量
int val = VALUE2; // 访问枚举常量
```
#### 枚举与整数转换
枚举类型不能隐式转换为整数类型，必须使用**static_cast**进行显式转换。
```cpp
int val = static_cast<int>(EnumName::VALUE1); // 显式转换枚举类型为整数
EnumName var = static_cast<EnumName>(1); // 显式转换整数为枚举类型
```

### 指针
概念：指针是一个变量，其值为另一个变量的地址，即内存位置的直接地址。

#### 相关运算符
- **&**：取地址运算符，返回变量的地址。
- **\***：解引用运算符，返回指针所指向地址的值。
- **->**：成员访问运算符，通过指针访问结构体或类的成员。
```cpp
int var = 42; // 声明一个整数变量
int* ptr = &var; // 声明一个指针变量并初始化为var的地址
int val = *ptr; // 解引用指针，获取var的值

struct MyStruct {
    int member;
};
MyStruct obj;
MyStruct* pObj = &obj; // 指向结构体的指针
pObj->member = 10; // 通过指针访问结构体成员
```

#### 分配内存
- 使用**new**运算符动态分配内存，返回指向新分配内存的指针。
- 使用**delete**运算符释放动态分配的内存，防止内存泄漏。
- 使用**malloc**和**free**函数分配和释放内存，需包含**<cstdlib>**头文件。
```cpp
int* ptr = new int; // 动态分配一个整数
*ptr = 42; // 赋值
delete ptr; // 释放内存
int* arr = new int [10]; // 动态分配一个整数数组
delete [] arr; // 释放数组内存

#include <cstdlib>
int* ptr = (int*)malloc(sizeof(int)); // 使用malloc分配内存
// ，malloc 函数返回的是一个 void* 类型的指针，而 void* 是一种通用指针类型，不能直接赋值给特定类型的指针（如 int*）。因此，需要显式地进行类型转换，将 void* 转换为目标类型的指针（如 int*）。
*ptr = 42; // 赋值
free(ptr); // 释放内存
```

#### 动态数组
```cpp
int size;
std::cin >> size; // 获取数组大小
int* arr = new int[size]; // 动态分配数组
// 使用数组(把指针当数组名使用)
for (int i = 0; i < size; i++) {
    arr[i] = i * 2; // 赋值
}
// 删除
delete [] arr; // 释放数组内存
```

#### 指针算术
指针可以进行加减运算，移动指针以访问数组元素。
即，指针加1实际上是增加了指针所指向类型的大小（以字节为单位）。
```cpp
int arr[5] = {10, 20, 30, 40, 50};
int* ptr = arr; // 指向数组第一个元素
for (int i = 0; i < 5; i++) {
    std::cout << *(ptr + i) << " "; // 访问数组元素
}
```
#### **指针数组**、**数组指针**和数组地址说明：
数组名被解释为第一个元素的地址，但对数组名使用**&**运算符时，返回的是整个数组的地址。
```cpp
int arr[5];
int* p1 = arr; // 指向第一个元素
int (*p2)[5] = &arr; // 指向整个数组(数组指针)
// (*ptrToArray)：表示 ptrToArray 是一个指针。
// [5]：表示指针指向的是一个包含 5 个 int 元素的数组。
std::cout << p1 << std::endl; // 输出第一个元素的地址
std::cout << p2 << std::endl; // 输出整个数组的地址
std::cout << arr << std::endl; // 输出第一个元素的地址
std::cout << &arr << std::endl; // 输出整个数组的地址

// 指针数组
int* ptrArr[5]; // 声明一个包含5个整数指针的数组
int a = 10, b = 20, c = 30, d = 40, e = 50;
ptrArr[0] = &a; // 初始化指针数组
ptrArr[1] = &b;
ptrArr[2] = &c;

// 数组指针
int (*arrPtr)[5] = &arr; // 声明一个指向包含5个整数的数组的指针
std::cout << (*arrPtr)[0] << std::endl; // 访问数组元素
```

#### 指向指针的指针
指向指针的指针（Pointer to Pointer）是一个指针变量，它存储另一个指针变量的地址。
它可以用于间接访问数据，特别是在多级指针操作中。
```cpp
int var = 42; // 声明一个整数变量
int* ptr = &var; // 声明一个指向整数的指针
int** pptr = &ptr; // 声明一个指向指针的指针
std::cout << var << std::endl; // 输出变量值
std::cout << *ptr << std::endl; // 通过指针访问变量值
std::cout << **pptr << std::endl; // 通过指向指针的指针访问变量值
```











