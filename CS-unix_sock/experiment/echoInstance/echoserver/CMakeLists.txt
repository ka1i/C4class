cmake_minimum_required(VERSION 3.10)
project(echoServer)


set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/${CMAKE_BUILD_TYPE}/bin/echoInstance)


add_executable(${PROJECT_NAME} "echoserver.c" "../../config.h")
target_link_libraries(${PROJECT_NAME} PRIVATE c)