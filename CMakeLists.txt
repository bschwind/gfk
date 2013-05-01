
cmake_minimum_required(VERSION 2.8)

# project name
project(GFK)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# Compiler-specific C++11 activation.
if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
    set(CMAKE_CXX_FLAGS "-std=c++11")
elseif ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "-stdlib=libc++")
	set(CMAKE_C_FLAGS "-stdlib=libc++")
endif ()
 
# setup version numbers
set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)

add_definitions(-Wall)

# add the GFK header path
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# add the subdirectories
add_subdirectory(src/GFK)

find_package(SFML 2.0 COMPONENTS system window graphics REQUIRED)
include_directories(${SFML_INCLUDE_DIR})
message(STATUS ${SFML_INCLUDE_DIR})

add_library( gfk STATIC
       ${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/Game.cpp
       ${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/GameTime.cpp
       ${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/Graphics/GraphicsDevice.cpp
       ${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/Graphics/Color.cpp
       ${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/Graphics/PackedColor.cpp
       ${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/Vector2.cpp
       ${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/MathHelper.cpp       
       )

target_link_libraries(gfk ${SFML_LIBRARIES})

add_subdirectory(test)
