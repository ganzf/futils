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
        src/Entities/Image.cpp src/Entities/Image.hpp src/Components/Clickable.cpp src/Components/Clickable.hpp src/Systems/SFML/Clickable.cpp src/Systems/SFML/Clickable.hpp src/Entities/Button.cpp src/Entities/Button.hpp src/Systems/SFML/Sprite.cpp src/Systems/SFML/Sprite.hpp src/Components/Sprite.cpp src/Components/Sprite.hpp src/Entities/Sprite.cpp src/Entities/Sprite.hpp)


if (UNIX)
	add_compile_options(-Wall -Wextra -Werror)
elseif(WIN32)
    set(CMAKE_CXX_FLAGS /std:c++latest)
#    add_compile_options(/std:c++latest)
endif()
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_library(fender STATIC ${SOURCE_FILES})
if (UNIX)
	target_link_libraries(fender sfml-system sfml-window sfml-audio sfml-graphics)
endif (UNIX)
if (WIN32)
#    set(SFML_ROOT ${PROJECT_SOURCE_DIR}/projects/fender/libraries/SFML/)
#    set(CMAKE_MODULE_PATH
#			${CMAKE_MODULE_PATH}
#			${PROJECT_SOURCE_DIR}/projects/fender/libraries/SFML/cmake/Modules/)
#	find_package(SFML REQUIRED COMPONENTS system window audio graphics)
#        message(${SFML_LIBRARIES})
#	target_link_libraries(fender ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
    target_link_libraries(fender
            ${PROJECT_SOURCE_DIR}/projects/fender/libraries/SFML/lib/sfml-system.lib
            ${PROJECT_SOURCE_DIR}/projects/fender/libraries/SFML/lib/sfml-window.lib
            ${PROJECT_SOURCE_DIR}/projects/fender/libraries/SFML/lib/sfml-audio.lib
            ${PROJECT_SOURCE_DIR}/projects/fender/libraries/SFML/lib/sfml-graphics.lib
            )
endif(WIN32)
target_link_libraries(fender -lstdc++fs)
include_directories(release include ${PROJECT_SOURCE_DIR}/utils src libraries/SFML/include)
