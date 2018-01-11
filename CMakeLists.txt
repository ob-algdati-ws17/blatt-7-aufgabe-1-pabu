cmake_minimum_required(VERSION 3.8)
project(AVLTree)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(avltree)

set(SOURCE_FILES main.cpp)
add_executable(Main ${SOURCE_FILES})

target_link_libraries(Main LINK_PUBLIC avltree)