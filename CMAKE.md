### 注释
```cmake
# 注释行

#[[
    注释块
]]
```

### 基础内容
``` cmake
cmake_minimum_required(VERSION 3.0) # 指定使用的 cmake 的最低版本
project(CALC)   # 工程名称
add_executable(app add.c div.c main.c mult.c sub.c) # 添加可执行文件名
```
cmake_minimum_required：指定使用的 cmake 的最低版本。
project：定义工程名称，并可指定工程的版本、工程描述、web主页地址、支持的语言（默认情况支持所有语言），如果不需要这些都是可以忽略的，只需要指定出工程名字即可。
```cmake
# PROJECT 指令的语法是：
project(<PROJECT-NAME> [<language-name>...])
project(<PROJECT-NAME>
       [VERSION <major>[.<minor>[.<patch>[.<tweak>]]]]
       [DESCRIPTION <project-description-string>]
       [HOMEPAGE_URL <url-string>]
       [LANGUAGES <language-name>...])
```
add_executable：定义工程会生成一个可执行程序
```cmake
add_executable(可执行程序名 源文件名称)
```

### CMake命令
```shell
$ mkdir build
$ cd build
$ cmake ..
$ make
```

### 私人订制
#### 定义变量
在上面的例子中一共提供了5个源文件，假设这五个源文件需要反复被使用，每次都直接将它们的名字写出来确实是很麻烦，此时我们就需要定义一个变量，将文件名对应的字符串存储起来，在cmake里定义变量需要使用set
```cmake
# SET 指令的语法是：
# [] 中的参数为可选项, 如不需要可以不写
SET(VAR [VALUE] [CACHE TYPE DOCSTRING [FORCE]])
```
VAR：变量名;
VALUE：变量值;

####  指定使用的C++标准
```
#增加-std=c++11
set(CMAKE_CXX_STANDARD 11)
#增加-std=c++14
set(CMAKE_CXX_STANDARD 14)
#增加-std=c++17
set(CMAKE_CXX_STANDARD 17)
```

####  指定输出的路径
在CMake中指定可执行程序输出的路径，也对应一个宏，叫做EXECUTABLE_OUTPUT_PATH，它的值还是通过set命令进行设置:
```
set(HOME /home/robin/Linux/Sort)
set(EXECUTABLE_OUTPUT_PATH ${HOME}/bin)
# 或
set_target_properties(chapter3 PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin) # 设置可执行文件输出目录
```

#### 搜索文件
如果一个项目里边的源文件很多，在编写CMakeLists.txt文件的时候不可能将项目目录的各个文件一一罗列出来，这样太麻烦也不现实。所以，在CMake中为我们提供了搜索文件的命令，可以使用aux_source_directory命令或者file命令。
```
aux_source_directory(< dir > < variable >)

cmake_minimum_required(VERSION 3.0)
project(CALC)
include_directories(${PROJECT_SOURCE_DIR}/include)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)
add_executable(app  ${SRC_LIST})
```
如果一个项目里边的源文件很多，在编写CMakeLists.txt文件的时候不可能将项目目录的各个文件一一罗列出来，这样太麻烦了。所以，在CMake中为我们提供了搜索文件的命令，他就是file（当然，除了搜索以外通过 file 还可以做其他事情）。

```
file(GLOB/GLOB_RECURSE 变量名 要搜索的文件路径和文件类型)

file(GLOB MAIN_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB MAIN_HEAD ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
```
GLOB: 将指定目录下搜索到的满足条件的所有文件名生成一个列表，并将其存储到变量中。
GLOB_RECURSE：递归搜索指定目录，将搜索到的满足条件的文件名生成一个列表，并将其存储到变量中。

#### 包含头文件
在编译项目源文件的时候，很多时候都需要将源文件对应的头文件路径指定出来，这样才能保证在编译过程中编译器能够找到这些头文件，并顺利通过编译。在CMake中设置要包含的目录也很简单，通过一个命令就可以搞定了，他就是include_directories:
```
cmake_minimum_required(VERSION 3.0)
project(CALC)
set(CMAKE_CXX_STANDARD 11)
set(HOME /home/robin/Linux/calc)
set(EXECUTABLE_OUTPUT_PATH ${HOME}/bin/)
include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
add_executable(app  ${SRC_LIST})
```

###  制作动态库或静态库
静态库：静态库是一个 .a（Linux/macOS）或 .lib（Windows） 文件，包含编译后的目标代码（.o 文件的集合）。在链接阶段，链接器会将静态库中被用到的函数代码直接复制到最终的可执行文件中。

动态库是一个 .so（Linux）、.dylib（macOS）或 .dll（Windows） 文件。链接时只记录依赖关系，运行时由操作系统动态加载库代码到内存。

####  制作静态/动态库
在cmake中，如果要制作静态库，需要使用的命令如下：
```
add_library(库名称 STATIC 源文件1 [源文件2] ...)    # 静态库
add_library(库名称 SHARED 源文件1 [源文件2] ...)    # 动态库
```
```
cmake_minimum_required(VERSION 3.0)
project(CALC)
include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB SRC_LIST "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
# 设置动态库/静态库生成路径
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
# 生成动态库
#add_library(calc SHARED ${SRC_LIST})
# 生成静态库
add_library(calc STATIC ${SRC_LIST})
```

#### 优缺点
| **对比项**       | **静态库（Static Library）**                                                                 | **动态库（Dynamic Library）**                                                           |
|------------------|----------------------------------------------------------------------------------------|-------------------------------------------------------------------------------------|
| **优点**         | - 打包到应用程序中，加载速度快<br>- 发布程序无需额外提供库文件，移植方便                                | - 可实现不同进程间资源共享<br>- 升级简单，只需替换库文件，无需重新编译<br>- 可控制加载时机，按需加载 |
| **缺点**         | - 相同库在多个程序中会重复加载，浪费内存和系统资源<br>- 库更新需重新编译整个项目，耗时                      | - 加载速度略慢于静态库（现代计算机性能下通常可忽略）                                           |

### 链接库
链接库的命令如下：
```
target_link_libraries(
    <target> 
    <PRIVATE|PUBLIC|INTERFACE> <item>... 
    [<PRIVATE|PUBLIC|INTERFACE> <item>...]...)
```
用于指定一个目标（如可执行文件或库）在编译时需要链接哪些库。它支持指定库的名称、路径以及链接库的顺序。

target：指定要加载的库的文件的名字
- 该文件可能是一个源文件
- 该文件可能是一个动态库/静态库文件
- 该文件可能是一个可执行文件

PRIVATE|PUBLIC|INTERFACE：动态库的访问权限，默认为PUBLIC
- 如果各个动态库之间没有依赖关系，无需做任何设置，三者没有没有区别，一般无需指定，使用默认的 PUBLIC 即可。
- 动态库的链接具有传递性，如果动态库 A 链接了动态库B、C，动态库D链接了动态库A，此时动态库D相当于也链接了动态库B、C，并可以使用动态库B、C中定义的方法。
```
target_link_libraries(A B C)
target_link_libraries(D A)
```
- PUBLIC：在public后面的库会被Link到前面的target中，并且里面的符号也会被导出，提供给第三方使用。
- PRIVATE：在private后面的库仅被link到前面的target中，并且终结掉，第三方不能感知你调了啥库
- INTERFACE：在interface后面引入的库不会被链接到前面的target中，只会导出符号。

#### 链接第三方动态库
在 CMake 中可以在生成可执行程序之前，通过命令指定出要链接的动态库的位置:
```
link_directories(path)
```

### 日志
在CMake中可以用用户显示一条消息，该命令的名字为message：
```
message([STATUS|WARNING|AUTHOR_WARNING|FATAL_ERROR|SEND_ERROR] "message to display" ...)
```
- (无) ：重要消息
- STATUS ：非重要消息
- WARNING：CMake 警告, 会继续执行
- AUTHOR_WARNING：CMake 警告 (dev), 会继续执行
- SEND_ERROR：CMake 错误, 继续执行，但是会跳过生成的步骤
- FATAL_ERROR：CMake 错误, 终止所有处理过程
CMake的命令行工具会在stdout上显示STATUS消息，在stderr上显示其他所有消息。CMake的GUI会在它的log区域显示所有消息。
CMake警告和错误消息的文本显示使用的是一种简单的标记语言。文本没有缩进，超过长度的行会回卷，段落之间以新行做为分隔符。

### 变量操作
#### 追加
使用set拼接
如果使用set进行字符串拼接，对应的命令格式如下：
```
set(变量名1 ${变量名1} ${变量名2} ...)
```
```cmake_minimum_required(VERSION 3.0)
project(TEST)
set(TEMP "hello,world")
file(GLOB SRC_1 ${PROJECT_SOURCE_DIR}/src1/*.cpp)
file(GLOB SRC_2 ${PROJECT_SOURCE_DIR}/src2/*.cpp)
# 追加(拼接)
set(SRC_1 ${SRC_1} ${SRC_2} ${TEMP})
message(STATUS "message: ${SRC_1}")
```

使用list进行字符串拼接，对应的命令格式如下：
```
list(APPEND <list> [<element> ...])
```
```
cmake_minimum_required(VERSION 3.0)
project(TEST)
set(TEMP "hello,world")
file(GLOB SRC_1 ${PROJECT_SOURCE_DIR}/src1/*.cpp)
file(GLOB SRC_2 ${PROJECT_SOURCE_DIR}/src2/*.cpp)
# 追加(拼接)
list(APPEND SRC_1 ${SRC_1} ${SRC_2} ${TEMP})
message(STATUS "message: ${SRC_1}")
```

#### 字符串移除
```
list(REMOVE_ITEM <list> <value> [<value> ...])
```
```
cmake_minimum_required(VERSION 3.0)
project(TEST)
set(TEMP "hello,world")
file(GLOB SRC_1 ${PROJECT_SOURCE_DIR}/*.cpp)
# 移除前日志
message(STATUS "message: ${SRC_1}")
# 移除 main.cpp
list(REMOVE_ITEM SRC_1 ${PROJECT_SOURCE_DIR}/main.cpp)
# 移除后日志
message(STATUS "message: ${SRC_1}")
```

#### 关于list命令还有其它功能

获取 list 的长度。

```CMAKE
list(LENGTH <list> <output variable>)
```

- LENGTH：子命令LENGTH用于读取列表长度
- <list>：当前操作的列表
- <output variable>：新创建的变量，用于存储列表的长度。

读取列表中指定索引的的元素，可以指定多个索引

```CMAKE
list(GET <list> <element index> [<element index> ...] <output variable>)
```

- <list>：当前操作的列表
- <element index>：列表元素的索引
- 从0开始编号，索引0的元素为列表中的第一个元素；
- 索引也可以是负数，-1表示列表的最后一个元素，-2表示列表倒数第二个元素，以此类推
- 当索引（不管是正还是负）超过列表的长度，运行会报错
- <output variable>：新创建的变量，存储指定索引元素的返回结果，也是一个列表。

将列表中的元素用连接符（字符串）连接起来组成一个字符串

```CMAKE
list (JOIN <list> <glue> <output variable>)
```

- <list>：当前操作的列表
- <glue>：指定的连接符（字符串）
- <output variable>：新创建的变量，存储返回的字符串

查找列表是否存在指定的元素，若果未找到，返回-1

```CMAKE
list(FIND <list> <value> <output variable>)
```

- <list>：当前操作的列表
- <value>：需要再列表中搜索的元素
- <output variable>：新创建的变量
- 如果列表<list>中存在<value>，那么返回<value>在列表中的索引.如果未找到则返回-1。

将元素追加到列表中

```CMAKE
list (APPEND <list> [<element> ...])
```

在list中指定的位置插入若干元素

```CMAKE
list(INSERT <list> <element_index> <element> [<element> ...])
```

将元素插入到列表的0索引位置

```CMAKE
list (PREPEND <list> [<element> ...])
```

将列表中最后元素移除

```CMAKE
list (POP_BACK <list> [<out-var>...])
```

将列表中第一个元素移除

```CMAKE
list (POP_FRONT <list> [<out-var>...])
```

将指定的元素从列表中移除

```CMAKE
list (REMOVE_ITEM <list> <value> [<value> ...])
```

将指定索引的元素从列表中移除

```CMAKE
list (REMOVE_AT <list> <index> [<index> ...])
```

### 宏定义

| 宏                         | 功能                                                         |
| :------------------------- | :----------------------------------------------------------- |
| `PROJECT_SOURCE_DIR`       | 使用cmake命令后紧跟的目录，一般是工程的根目录                |
| `PROJECT_BINARY_DIR`       | 执行cmake命令的目录                                          |
| `CMAKE_CURRENT_SOURCE_DIR` | 当前处理的CMakeLists.txt所在的路径                           |
| `CMAKE_CURRENT_BINARY_DIR` | target 编译目录                                              |
| `EXECUTABLE_OUTPUT_PATH`   | 重新定义目标二进制可执行文件的存放位置                       |
| `LIBRARY_OUTPUT_PATH`      | 重新定义目标链接库文件的存放位置                             |
| `PROJECT_NAME`             | 返回通过PROJECT指令定义的项目名称                            |
| `CMAKE_BINARY_DIR`         | 项目实际构建路径，假设在build目录进行的构建，那么得到的就是这个目录的路径 |

### 嵌套的CMake
如果项目很大，或者项目中有很多的源码目录，在通过CMake管理项目的时候如果只使用一个CMakeLists.txt，那么这个文件相对会比较复杂，有一种化繁为简的方式就是给每个源码目录都添加一个CMakeLists.txt文件（头文件目录不需要），这样每个文件都不会太复杂，而且更灵活，更容易维护。

#### 准备工作
```
$ tree
.
├── build
├── calc
│   ├── add.cpp
│   ├── CMakeLists.txt
│   ├── div.cpp
│   ├── mult.cpp
│   └── sub.cpp
├── CMakeLists.txt
├── include
│   ├── calc.h
│   └── sort.h
├── sort
│   ├── CMakeLists.txt
│   ├── insert.cpp
│   └── select.cpp
├── test1
│   ├── calc.cpp
│   └── CMakeLists.txt
└── test2
    ├── CMakeLists.txt
    └── sort.cpp

6 directories, 15 files
```
##### 节点关系

众所周知，Linux的目录是树状结构，所以嵌套的 CMake 也是一个树状结构，最顶层的 CMakeLists.txt 是根节点，其次都是子节点。因此，我们需要了解一些关于 CMakeLists.txt 文件变量作用域的一些信息：
- 根节点CMakeLists.txt中的变量全局有效
- 父节点CMakeLists.txt中的变量可以在子节点中使用
- 子节点CMakeLists.txt中的变量只能在当前节点中使用

##### 添加子目录
接下来我们还需要知道在 CMake 中父子节点之间的关系是如何建立的，这里需要用到一个 CMake 命令：
```
add_subdirectory(source_dir [binary_dir] [EXCLUDE_FROM_ALL])
```
- source_dir：指定了CMakeLists.txt源文件和代码文件的位置，其实就是指定子目录
- binary_dir：指定了输出文件的路径，一般不需要指定，忽略即可。
- EXCLUDE_FROM_ALL：在子路径下的目标默认不会被包含到父路径的ALL目标里，并且也会被排除在IDE工程文件之外。用户必须显式构建在子路径下的目标。

#### 各节点内容
##### 根目录
```
cmake_minimum_required(VERSION 3.0)
project(test)
# 定义变量
# 静态库生成的路径
set(LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)
# 测试程序生成的路径
set(EXEC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
# 头文件目录
set(HEAD_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include)
# 静态库的名字
set(CALC_LIB calc)
set(SORT_LIB sort)
# 可执行程序的名字
set(APP_NAME_1 test1)
set(APP_NAME_2 test2)
# 添加子目录
add_subdirectory(calc)
add_subdirectory(sort)
add_subdirectory(test1)
add_subdirectory(test2)
```
##### 链接库
```
cmake_minimum_required(VERSION 3.0)
project(CALCLIB)
aux_source_directory(./ SRC)
include_directories(${HEAD_PATH})
set(LIBRARY_OUTPUT_PATH ${LIB_PATH})
add_library(${CALC_LIB} STATIC ${SRC})
```

```
cmake_minimum_required(VERSION 3.0)
project(SORTLIB)
aux_source_directory(./ SRC)
include_directories(${HEAD_PATH})
set(LIBRARY_OUTPUT_PATH ${LIB_PATH})
add_library(${SORT_LIB} SHARED ${SRC})
```
##### test1 目录
```
cmake_minimum_required(VERSION 3.0)
project(CALCTEST)
aux_source_directory(./ SRC)
include_directories(${HEAD_PATH})   # 指定头文件路径，HEAD_PATH变量是在根节点文件中定义的
link_directories(${LIB_PATH})  
link_libraries(${CALC_LIB}) # 指定可执行程序要链接的静态库，CALC_LIB变量是在根节点文件中定义的
set(EXECUTABLE_OUTPUT_PATH ${EXEC_PATH})    # 指定可执行程序生成的路径，EXEC_PATH变量是在根节点文件中定义的
add_executable(${APP_NAME_1} ${SRC})    # 生成可执行程序，APP_NAME_1变量是在根节点文件中定义的
```
##### test2 目录
```
cmake_minimum_required(VERSION 3.0)
project(SORTTEST)
aux_source_directory(./ SRC)
include_directories(${HEAD_PATH})
set(EXECUTABLE_OUTPUT_PATH ${EXEC_PATH})
link_directories(${LIB_PATH})
add_executable(${APP_NAME_2} ${SRC})
target_link_libraries(${APP_NAME_2} ${SORT_LIB})
```

### 流程控制
#### 条件判断
```
if(<condition>)
  <commands>
elseif(<condition>) # 可选快, 可以重复
  <commands>
else()              # 可选快
  <commands>
endif()
```
- 如果是1, ON, YES, TRUE, Y, 非零值，非空字符串时，条件判断返回True
- 如果是 0, OFF, NO, FALSE, N, IGNORE, NOTFOUND，空字符串时，条件判断返回False

#### 逻辑判断
```
if(NOT <condition>)
```
其实这就是一个取反操作，如果条件condition为True将返回False，如果条件condition为False将返回True。

```
if(<cond1> AND <cond2>)
```
如果cond1和cond2同时为True，返回True否则返回False。

```
if(<cond1> OR <cond2>)
```
如果cond1和cond2两个条件中至少有一个为True，返回True，如果两个条件都为False则返回False。

#### 比较
基于数值的比较
```
if(<variable|string> LESS <variable|string>)
if(<variable|string> GREATER <variable|string>)
if(<variable|string> EQUAL <variable|string>)
if(<variable|string> LESS_EQUAL <variable|string>)
if(<variable|string> GREATER_EQUAL <variable|string>)
```
- LESS：如果左侧数值小于右侧，返回True
- GREATER：如果左侧数值大于右侧，返回True
- EQUAL：如果左侧数值等于右侧，返回True
- LESS_EQUAL：如果左侧数值小于等于右侧，返回True

基于字符串的比较
```
if(<variable|string> STRLESS <variable|string>)
if(<variable|string> STRGREATER <variable|string>)
if(<variable|string> STREQUAL <variable|string>)
if(<variable|string> STRLESS_EQUAL <variable|string>)
if(<variable|string> STRGREATER_EQUAL <variable|string>)
```
- STRLESS：如果左侧字符串小于右侧，返回True
- STRGREATER：如果左侧字符串大于右侧，返回True
- STREQUAL：如果左侧字符串等于右侧，返回True
- STRLESS_EQUAL：如果左侧字符串小于等于右侧，返回True
- STRGREATER_EQUAL：如果左侧字符串大于等于右侧，返回True

#### 文件操作
判断文件或者目录是否存在```if(EXISTS path-to-file-or-directory)```

判断是不是目录```if(IS_DIRECTORY path)```

判断是不是软连接```if(IS_SYMLINK file-name)```

判断是不是绝对路径```if(IS_ABSOLUTE path)```

#### 循环
##### foreach
```
foreach(<loop_var> <items>)
    <commands>
endforeach()
```
通过foreach我们就可以对items中的数据进行遍历，然后通过loop_var将遍历到的当前的值取出，在取值的时候有以下几种用法：

```foreach(<loop_var> RANGE <stop>)```
- RANGE：关键字，表示要遍历范围
- stop：这是一个正整数，表示范围的结束值，在遍历的时候从 0 开始，最大值为 stop。
- loop_var：存储每次循环取出的值

```foreach(<loop_var> RANGE <start> <stop> [<step>])```
- RANGE：关键字，表示要遍历范围
- start：这是一个正整数，表示范围的起始值，也就是说最小值为 start
- stop：这是一个正整数，表示范围的结束值，也就是说最大值为 stop
- step：控制每次遍历的时候以怎样的步长增长，默认为1，可以不设置
- loop_var：存储每次循环取出的值

```foreach(<loop_var> IN [LISTS [<lists>]] [ITEMS [<items>]])```
- IN：关键字，表示在 xxx 里边
- LISTS：关键字，对应的是列表list，通过set、list可以获得
- ITEMS：关键字，对应的也是列表
- loop_var：存储每次循环取出的值
```
cmake_minimum_required(VERSION 3.2)
project(test)
# 创建 list
set(WORD a b c d)
set(NAME ace sabo luffy)
# 遍历 list
foreach(item IN LISTS WORD NAME)
    message(STATUS "当前遍历的值为: ${item}" )
endforeach()
```

```foreach(<loop_var>... IN ZIP_LISTS <lists>)```
```
cmake_minimum_required(VERSION 3.17)
project(test)
# 通过list给列表添加数据
list(APPEND WORD hello world "hello world")
list(APPEND NAME ace sabo luffy zoro sanji)
# 遍历列表
foreach(item1 item2 IN ZIP_LISTS WORD NAME)
    message(STATUS "当前遍历的值为: item1 = ${item1}, item2=${item2}" )
endforeach()

message("=============================")
# 遍历列表
foreach(item  IN ZIP_LISTS WORD NAME)
    message(STATUS "当前遍历的值为: item1 = ${item_0}, item2=${item_1}" )
endforeach()
```

##### while
```
while(<condition>)
    <commands>
endwhile()
```
```
cmake_minimum_required(VERSION 3.5)
project(test)
# 创建一个列表 NAME
set(NAME luffy sanji zoro nami robin)
# 得到列表长度
list(LENGTH NAME LEN)
# 循环
while(${LEN} GREATER  0)
    message(STATUS "names = ${NAME}")
    # 弹出列表头部元素
    list(POP_FRONT NAME)
    # 更新列表长度
    list(LENGTH NAME LEN)
endwhile()
```
