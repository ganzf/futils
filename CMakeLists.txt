cmake_minimum_required(VERSION 3.8)
project(futils)

execute_process(COMMAND "git submodule update --remote")
add_subdirectory(projects)
add_subdirectory(tests)
