cmake_minimum_required(VERSION 2.8)
project(GFK)

set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

if (APPLE)
	set(CMAKE_OSX_ARCHITECTURES x86_64)
endif()

# Compiler-specific C++11 activation.
if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
	set(CMAKE_CXX_FLAGS "-std=c++0x")
elseif ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
	set(CMAKE_CXX_FLAGS "-stdlib=libc++")
	set(CMAKE_C_FLAGS "-stdlib=libc++")
endif ()

add_definitions(-Wall)

# Find libraries
find_package(GLEW REQUIRED)
find_package(GLFW REQUIRED)

# Add header paths
include_directories(${GLEW_INCLUDE_PATH})
include_directories(${GLFW_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Add the subdirectories
add_subdirectory(src/GFK)

add_library(gfk-math STATIC
			${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/Math/Vector2.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/Math/Vector3.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/Math/MathHelper.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/Math/Matrix.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/Math/Quaternion.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/Math/Transform.cpp
			)

add_library(gfk-graphics STATIC
			${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/Graphics/GraphicsDevice.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/Graphics/Color.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/Graphics/PackedColor.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/Graphics/Shader.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/Graphics/MonitorConfig.cpp
			)

add_library(gfk-network STATIC
			${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/Network/UDPSocket.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/Network/IPAddress.cpp
			)

add_library(gfk STATIC
			${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/Game.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/GameTime.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/Components/GameObject.cpp
)

target_link_libraries(gfk-graphics ${GLEW_LIBRARY} ${GLFW_LIBRARY})

target_link_libraries(gfk gfk-math gfk-graphics gfk-network)

add_subdirectory(test)
