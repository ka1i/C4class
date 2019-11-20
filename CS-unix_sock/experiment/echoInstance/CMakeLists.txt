cmake_minimum_required(VERSION 3.10)

project(echo)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}/bin/echoInstance)

include_directories("../")

add_subdirectory(echoserver)
add_subdirectory(echoclient)
