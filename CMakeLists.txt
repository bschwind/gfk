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
	set(CMAKE_CXX_FLAGS "-stdlib=libc++ -std=c++11")
	set(CMAKE_C_FLAGS "-stdlib=libc++")
endif ()

add_definitions(-Wall)

# Set up external libraries
find_package(GLEW REQUIRED)
find_package(Libuv REQUIRED)

# Link against libuuid for Linux
if (NOT WIN32 AND NOT APPLE)
	find_package(UUID)
endif ()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/assimp)

# Add header paths
include_directories(${GLEW_INCLUDE_PATH})
include_directories(${LIBUV_INCLUDE_PATH})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/assimp/include)
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
			${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/Math/GUIDGenerator.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/Math/EasingFunctions.cpp
			)

add_library(gfk-input STATIC
	${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/Input/Keyboard.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/Input/Mouse.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/Input/GamePad.cpp
)

add_library(gfk-graphics STATIC
			${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/Graphics/GraphicsDevice.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/Graphics/Color.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/Graphics/PackedColor.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/Graphics/Shader.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/Graphics/MonitorConfig.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/Graphics/PrimitiveBatch2D.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/Graphics/PrimitiveBatch3D.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/Graphics/Camera.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/Graphics/Camera2D.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/Graphics/Mesh.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/Graphics/AssImpBridge.cpp
			)

add_library(gfk-network STATIC
			${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/Network/UDPSocket.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/Network/IPAddress.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/Network/UDPServer.cpp
			)

add_library(gfk-system STATIC
			${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/System/Logger.cpp
			)

add_library(gfk STATIC
			${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/Game.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/GameTime.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/Components/GameObject.cpp
)

target_link_libraries(gfk-network ${LIBUV_LIBRARY} gfk-system)

target_link_libraries(gfk-graphics ${GLEW_LIBRARY} glfw ${GLFW_LIBRARIES} assimp gfk-system)
target_link_libraries(gfk-input gfk-math gfk-system)

if (NOT WIN32 AND NOT APPLE)
	target_link_libraries(gfk-math ${UUID_LIBRARY} gfk-system)
endif ()

target_link_libraries(gfk gfk-math gfk-input gfk-graphics gfk-network gfk-system)

add_subdirectory(test)
