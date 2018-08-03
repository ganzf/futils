cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 17)
project(orias)

function(find_static_library LIB_NAME OUT)
	if (WIN32 OR MSVC)
		set(CMAKE_FIND_LIBRARY_SUFFIXES ".lib")
	elseif (UNIX)
		set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
	endif()
	find_library(
			FOUND_${LIB_NAME}_STATIC
			${LIB_NAME}
	)
	if (FOUND_${LIB_NAME}_STATIC)
		get_filename_component(ABS_FILE ${FOUND_${LIB_NAME}_STATIC} ABSOLUTE)
	else()
		message(SEND_ERROR "Unable to find library ${LIB_NAME}")
	endif()
	set(${OUT} ${ABS_FILE} PARENT_SCOPE)
endfunction()

file(GLOB GameObjects include/GameObjects/UI/* include/GameObjects/Game/*)
file(GLOB JsonCPP include/json/*.cpp include/json/*.hpp include/json/json/*.h)
set(SOURCE_FILES
		src/main.cpp
		src/Systems/Splashscreen.cpp
		src/Systems/Game.cpp
		${GameObjects}
		${JsonCPP}
		)

add_executable(orias ${SOURCE_FILES})
include_directories(include futils)
set_target_properties(orias PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../)
if (UNIX)
target_compile_options(orias PUBLIC -W -Wall -Werror -Wextra -g3)
target_link_libraries(orias ${CMAKE_SOURCE_DIR}/lib/libfender.a dl)
target_link_libraries(orias sfml-system sfml-window sfml-audio sfml-graphics)
endif (UNIX)
if (WIN32)
find_library(FENDER fender HINTS ./lib)
find_library(SFMLSYSTEM sfml-system HINTS ./lib)
find_library(SFMLWINDOW sfml-window HINTS ./lib)
find_library(SFMLAUDIO sfml-audio HINTS ./lib)
find_library(SFMLGRAPHICS sfml-graphics HINTS ./lib)
target_link_libraries(orias ${FENDER})
message("Found ${FENDER}")
target_link_libraries(orias ${SFMLSYSTEM} ${SFMLAUDIO} ${SFMLGRAPHICS} ${SFMLWINDOW})
endif (WIN32)
target_link_libraries(orias -lstdc++fs)
