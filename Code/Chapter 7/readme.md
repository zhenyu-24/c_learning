## 文件
1. protos.cpp -函数原型说明
2. lotto.cpp - 简单的long double公式计算
3. arrfun2.cpp -函数与数组（地址，sizeof说明）
4. arrfun3.cpp -填充数组

## C++ 函数返回值
不能是数组但可以说其他任何类型——整数、浮点数、指针以及表达式、   结构和对象（可以将数组转为结构或对象的组成部分返回）

## C++ 原型（protos.cpp）
1.  编程风格：先原型，再放main()，最后函数定义。
2.  函数原型有参数类型列表即行，即void cheers(int)
3.  C++会自动转换参数为原型中指定的类型，条件是两者都是算术类型，例如cheers(cube(2)),cube将2转为2.0返回8.0,cheers再将8.0转为8

## 函数与数组
1. int fun(int * arr, int n)与int fun(int arr[], int n)皆可
2. C++将数组名解释为其第一个元素的地址。但对数组名使用`sizeof`将得到整个数组长度（函数中是元素长度，故要显式传递数组长度），使用`&`用于数组名将返回整个数组的地址。
3. arr[i] == *(arr + i); &arr[i] == arr + i
