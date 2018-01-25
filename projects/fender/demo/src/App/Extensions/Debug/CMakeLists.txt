cmake_minimum_required(VERSION 3.9)
project(Debug)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_library(Debug SHARED Debug.cpp Debug.hpp)
include_directories(../../../../../src ../../../../../include ../../../../../utils)
find_library(FENDER fender HINTS ../)
target_link_libraries(Debug ${FENDER})