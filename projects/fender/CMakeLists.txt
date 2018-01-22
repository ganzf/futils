cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 17)

file(GLOB INCLUDE
		"include/*.hpp"
		)
file(GLOB UTILS
  "${PROJECT_SOURCE_DIR}/utils/*.hpp")
file(GLOB SYSTEMS
		"src/Systems/*.cpp"
		"src/Systems/*.hpp"
		"src/Systems/SFML/*.cpp"
		"src/Systems/SFML/*.hpp"
		"src/Systems/Fysics/*.cpp"
		"src/Systems/Fysics/*.hpp")
file(GLOB ENTITIES
		"src/Entities/*.cpp"
		"src/Entities/*.hpp")
file(GLOB COMPONENTS
		"src/Components/*.cpp"
		"src/Components/*.hpp")
file(GLOB SRC
		"src/*.cpp")

set(SOURCE_FILES
		${INCLUDE}
		${UTILS}
		${ENTITIES}
		${COMPONENTS}
		${SYSTEMS}
		${SRC}
        src/Entities/Image.cpp src/Entities/Image.hpp src/Components/Clickable.cpp src/Components/Clickable.hpp src/Systems/SFML/Clickable.cpp src/Systems/SFML/Clickable.hpp src/Entities/Button.cpp src/Entities/Button.hpp)

if (UNIX)
	add_compile_options(-Wall -Wextra -Werror)
endif(UNIX)

add_library(fender STATIC ${SOURCE_FILES})

if (UNIX)
	target_link_libraries(fender sfml-system sfml-window sfml-audio sfml-graphics)
endif (UNIX)
if (WIN32)
	target_link_libraries(fender libraries/SFML/lib/sfml-system libraries/SFML/lib/sfml-window libraries/SFML/lib/sfml-audio libraries/SFML/lib/sfml-graphics)
endif(WIN32)
target_link_libraries(fender -lstdc++fs)
include_directories(release include ${PROJECT_SOURCE_DIR}/utils src libraries/SFML/include)
