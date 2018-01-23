cmake_minimum_required(VERSION 3.8)
project(futils)

set(FENDER_ROOT ${PROJECT_SOURCE_DIR}/projects/fender)
set(MUTILS_ROOT ${PROJECT_SOURCE_DIR}/projects/mutils)
set(DEMO_ROOT ${PROJECT_SOURCE_DIR}/projects/fender/demo)

execute_process(
        COMMAND git submodule update --remote --init
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)
add_subdirectory(projects)
add_subdirectory(tests)
