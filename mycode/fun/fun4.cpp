#include "fun4.h"  // 引用自己的头文件
#include <iostream>
#include <string>
#include <cstring>

// 把你原来的函数体复制到这里
void test_array() {
    int a[5] = {1, 2, 3, 4, 5};
    int b[5] = {1, 2, 3};
    int c[] = {1, 2, 3, 4, 5};
    int num_elements = sizeof(c) / sizeof(c[0]);
    std::cout << "num_elements: " << num_elements << std::endl;
    std::cout << "sizeof(c): " << sizeof(c) << std::endl;
    std::cout << "sizeof(c[0]): " << sizeof(c[0]) << std::endl;
    std::cout << "Array address:" << c << std::endl;
}

void test_char_array() {
    char cat[4] = {'c', 'a', 't', '\0'};
    char dog[4] = "dog";
    std::cout << "cat: " << cat << std::endl;
    std::cout << "dog: " << dog << std::endl;

    std::cout << "I give me right ar"
    "m to be a great violinist.\n";

    char name2[20];
    char name3[20];
    std::cout << "Enter your name:";
    std::cin.getline(name2, 20);
    std::cout << "Your name is " << name2 << " and it has " << std::strlen(name2) << " characters.\n";
    std::cout << "Enter your favorite food:";
    std::cin.getline(name3, 20);
    std::cout << "Your favorite food is " << name3 << " and it has " << std::strlen(name3) << " characters.\n";

    std::cout << "Enter your house bulit?";
    int year;
    std::cin >> year;
    std::cin.get();  // 丢弃换行符
    std::cout << "Your house was built in " << year << std::endl;
    std::cout << "Enter your address:";
    char address[80];
    std::cin.getline(address, 80);
    std::cout << "Your address is " << address << std::endl;
}

void test_string() {
    std::string str1;
    std::cout << "Enter a string: ";
    std::getline(std::cin, str1);
    std::cout << "str1: " << str1 << std::endl;

    std::string str2 = "Hello";
    std::string str3 = "World";
    std::string str4 = str2 + " " + str3;
    std::cout << "str4: " << str4 << std::endl;

    char charr1[20];
    char charr2[20] = "Hello";
    std::strcpy(charr1, charr2);
    std::strcat(charr1, " World");

    std::cout << "str4.size(): " << str4.size() << std::endl;
    std::cout << "str4.length(): " << str4.length() << std::endl;
    std::cout << "str4[0]: " << str4[0] << std::endl;
    std::cout << "str4.at(0): " << str4.at(0) << std::endl;
    std::cout << "str4.front(): " << str4.front() << std::endl;
    std::cout << "str4.back(): " << str4.back() << std::endl;
    std::cout << "str4.empty(): " << str4.empty() << std::endl;
    std::cout << "str4.capacity(): " << str4.capacity() << std::endl;
    std::cout << "str4.max_size(): " << str4.max_size() << std::endl;
    std::cout << "str4.c_str(): " << str4.c_str() << std::endl;
    std::cout << "str4.data(): " << str4.data() << std::endl;
    std::cout << "str4.find(\"World\"): " << str4.find("World") << std::endl;
    std::cout << "str4.find_first_of(\"World\"): " << str4.find_first_of("World") << std::endl;
    std::cout << "str4.find_last_of(\"World\"): " << str4.find_last_of("World") << std::endl;
}

void test_struct() {
    struct inflatable {
        std::string name;
        float volume;
        double price;
    };
    inflatable guest = {
        "Glorious Gloria",
        1.88,
        29.99
    };
    inflatable pal = {
        "Audacious Arthur",
        3.12,
        32.99
    };
    std::cout << "guest.name: " << guest.name << std::endl;

    inflatable guests[2] = {
        {"Bambi", 0.5, 21.99},
        {"Godzilla", 2000, 565.99}
    };
}

void test_union() {
    union one4all {
        int int_val;
        long long_val;
        double double_val;
    };
    one4all pail;
    pail.int_val = 15;
    std::cout << "pail.int_val: " << pail.int_val << std::endl;
    pail.double_val = 1.38;
    std::cout << "pail.double_val: " << pail.double_val << std::endl;

    struct widget {
        char brand[20];
        int type;
        union id {
            long id_num;
            char id_char[20];
        } id_val;
    };
}

void test_enum() {
    enum spectrum {red, orange, yellow, green, blue, violet, indigo, ultraviolet};
    spectrum band = blue;
    int color = orange + blue;
    std::cout << "color: " << color << std::endl;
    std::cout << "band: " << band << std::endl;
    std::cout << "blue: " << blue << std::endl;

    enum Month {
        Jan = 1, Feb, Mar, Apr, May, Jun,
        Jul, Aug, Sep, Oct, Nov, Dec
    };
}

void test_pointer() {
    int a = 10;
    int* ptr = &a;
    std::cout << *ptr << std::endl;
    std::cout << ptr << std::endl;

    int& b = a;
    b = 20;
    std::cout << "a: " << a << std::endl;
}