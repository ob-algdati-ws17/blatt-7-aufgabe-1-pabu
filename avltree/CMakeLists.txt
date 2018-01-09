cmake_minimum_required(VERSION 3.8)

set(SOURCE_FILES AVLTree.cpp AVLTree.h)
add_library (avltree ${SOURCE_FILES})

target_include_directories(avltree PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})