cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 17)

file(GLOB MODULES_SRC ${DEMO_ROOT}/src/App/Modules/*.cpp)
file(GLOB MODULES_HPP ${DEMO_ROOT}/src/App/Modules/*.hpp)

set(SOURCE_FILES
		src/main.cpp
		src/App/App.cpp)

add_executable(demoExe ${SOURCE_FILES} ${MODULES_SRC} ${MODULES_HPP})

include_directories(
  ${FENDER_ROOT}/include
  ${FENDER_ROOT}/src
  ${PROJECT_SOURCE_DIR}/utils
  include
  src ../include)

set_target_properties(demoExe PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${DEMO_ROOT})

if (UNIX)
target_compile_options(demoExe PUBLIC -W -Wall -Werror -Wextra -g3)
target_link_libraries(demoExe dl)
endif (UNIX)
if (WIN32)
#target_link_libraries(demoExe ${SFMLSYSTEM} ${SFMLAUDIO} ${SFMLGRAPHICS} ${SFMLWINDOW})
endif (WIN32)
target_link_libraries(demoExe fender)
#target_link_libraries(demoExe sfml-system sfml-window sfml-audio sfml-graphics)
target_link_libraries(demoExe -lstdc++fs)
