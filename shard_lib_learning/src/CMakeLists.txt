cmake_minimum_required(VERSION 3.1)
project(uselib)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

add_definitions("-Wl,-rpath,/opt/learnCmake/lib")
link_directories("/opt/learnCmake/lib")

include_directories("../libhello/src/")

add_executable(${PROJECT_NAME} main.c)#设置为输出的可执行文件,即输出main这个可执行文件
target_link_libraries(${PROJECT_NAME} PRIVATE hello)



