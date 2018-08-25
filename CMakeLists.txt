cmake_minimum_required(VERSION 3.8)
project(myhindex)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Hindex.cpp Hindex.h tool.h)
add_executable(myhindex ${SOURCE_FILES})