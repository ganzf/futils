cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 17)
project(demo)

#function(find_static_library LIB_NAME OUT)
#	if (WIN32 OR MSVC)
#		set(CMAKE_FIND_LIBRARY_SUFFIXES ".lib")
#	elseif (UNIX)
#		set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
#	endif()
#	find_library(
#			FOUND_${LIB_NAME}_STATIC
#			${LIB_NAME}
#	)
#	if (FOUND_${LIB_NAME}_STATIC)
#		get_filename_component(ABS_FILE ${FOUND_${LIB_NAME}_STATIC} ABSOLUTE)
#	else()
#		message(SEND_ERROR "Unable to find library ${LIB_NAME}")
#	endif()
#	set(${OUT} ${ABS_FILE} PARENT_SCOPE)
#endfunction()

set(SOURCE_FILES
		src/main.cpp
		src/App/App.cpp
		src/App/Modules/WindowTest.cpp
		src/App/Modules/OtherSystem.cpp)

add_executable(demoExe ${SOURCE_FILES})
include_directories(include utils ../src)
set_target_properties(demoExe PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
if (UNIX)
target_compile_options(demoExe PUBLIC -W -Wall -Werror -Wextra -g3)
target_link_libraries(demoExe fender dl)
target_link_libraries(demoExe sfml-system sfml-window sfml-audio sfml-graphics)
endif (UNIX)
if (WIN32)
#find_library(FENDER fender HINTS ./lib)
find_library(SFMLSYSTEM sfml-system HINTS ./lib)
find_library(SFMLWINDOW sfml-window HINTS ./lib)
find_library(SFMLAUDIO sfml-audio HINTS ./lib)
find_library(SFMLGRAPHICS sfml-graphics HINTS ./lib)
target_link_libraries(demo fender)
#message("Found ${FENDER}")
target_link_libraries(demoExe ${SFMLSYSTEM} ${SFMLAUDIO} ${SFMLGRAPHICS} ${SFMLWINDOW})
endif (WIN32)
target_link_libraries(demoExe -lstdc++fs)