cmake_minimum_required(VERSION 3.0) # 指定使用的 cmake 的最低版本

project(test)   # 工程名称

set(CMAKE_CXX_STANDARD 11) # 指定 C++11 标准

include_directories(${CMAKE_SOURCE_DIR}/fun) # 包含头文件目录

file(GLOB FUN_SOURCES "fun/*.cpp") # 获取 fun 目录下的所有源文件

# 设置链接库生成路径
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)
link_directories(${CMAKE_SOURCE_DIR}/lib) # 设置链接库搜索路径
add_library(fun SHARED ${FUN_SOURCES})  # 生成动态链接库
# add_library(fun STATIC ${FUN_SOURCES}) # 生成静态链接库

# set(CHAPTER4_LIST chapter4.cpp ${FUN_SOURCES}) # 添加源文件列表
# add_executable(chapter4 ${CHAPTER4_LIST}) # 添加可执行文件名

add_executable(chapter3 chapter3.cpp)
target_link_libraries(chapter3 PUBLIC fun)
add_executable(chapter4 chapter4.cpp)
target_link_libraries(chapter4 PUBLIC fun)

set_target_properties(chapter3 PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin) # 设置可执行文件输出目录
set_target_properties(chapter4 PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin) # 设置可执行文件输出目录