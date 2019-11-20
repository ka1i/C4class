cmake_minimum_required(VERSION 3.2)
project(hello)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

include_directories("./src")

aux_source_directory(./src SRC_DIR)

add_library(${PROJECT_NAME} SHARED ${SRC_DIR})
target_link_libraries(${PROJECT_NAME})
