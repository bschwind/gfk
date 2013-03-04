
cmake_minimum_required(VERSION 2.8)

# project name
project(GFK)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# setup version numbers
set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)

add_definitions(-Wall)

# add the GFK header path
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# add the subdirectories
add_subdirectory(src/GFK)

find_package(SFML 1 COMPONENTS system window REQUIRED)
include_directories(${SFML_INCLUDE_DIR})
message(STATUS ${SFML_INCLUDE_DIR})

add_library( gfk STATIC
       ${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/Game.cpp
       ${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/GameTime.cpp
       ${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/Graphics/GraphicsDevice.cpp
       )

target_link_libraries(gfk ${SFML_LIBRARIES})

add_subdirectory(test)
