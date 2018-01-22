cmake_minimum_required(VERSION 3.8)
project(futils)

execute_process(
        COMMAND git submodule update --remote --init
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)
add_subdirectory(projects)
add_subdirectory(tests)
