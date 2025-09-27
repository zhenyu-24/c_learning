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

### 流程控制

