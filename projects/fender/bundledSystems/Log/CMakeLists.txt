cmake_minimum_required(VERSION 3.9)
project(Log VERSION 1.0 DESCRIPTION "Log system for fender")
add_library(Log SHARED Log.cpp Log.hpp include/events.hpp)
target_include_directories(Log PUBLIC include utils)
set_target_properties(Log PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(Log PROPERTIES PUBLIC_HEADER Log.hpp)

