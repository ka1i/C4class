cmake_minimum_required(VERSION 3.10)

project(CS-unix_sock)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}/bin)

add_subdirectory(experiment/echoInstance)
#add_subdirectory(experiment/ntpInstance)
