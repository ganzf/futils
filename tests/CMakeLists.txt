#
# Futils Project - Unit tests
# Created by Ganzf on 21/11/17
#

cmake_minimum_required(VERSION 3.9)
set(CMAKE_CXX_STANDARD 17)

# utils/Header.hpp TestFile.cpp
set(SOURCES
  ${PROJECT_SOURCE_DIR}/utils/callback.hpp Callback.cpp
  )
add_executable(tests ${SOURCES})
include_directories(${PROJECT_SOURCE_DIR}/utils)

if(UNIX)
    target_link_libraries(tests criterion pthread dl)
elseif(WIN32)
    target_link_libraries(tests lib/criterion.lib)
endif()
