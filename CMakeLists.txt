cmake_minimum_required(VERSION 2.8)
project(GFK)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# Use 64-bit if on OS X
if (APPLE)
	set(CMAKE_OSX_ARCHITECTURES x86_64)
	# These flags are required for GLFW to link properly
	set(CMAKE_CXX_LINK_FLAGS "-framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo")
endif()

# Compiler-specific C++11 activation.
if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
	set(CMAKE_CXX_FLAGS "-std=c++0x")
elseif ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
	set(CMAKE_CXX_FLAGS "-stdlib=libc++ -std=c++11")
	set(CMAKE_C_FLAGS "-stdlib=libc++")
endif ()

# Enable all warnings
add_definitions(-Wall -Wextra)

# Set up external libraries
find_package(GLEW_STATIC REQUIRED)
find_package(GLFW REQUIRED)
find_package(ASSIMP REQUIRED)
find_package(OVR REQUIRED)

# Link against libuuid for Linux
if (NOT WIN32 AND NOT APPLE)
	find_package(UUID)
endif ()

# Add header paths
include_directories(${GLEW_INCLUDE_PATH})
include_directories(${GLFW_INCLUDE_PATH})
include_directories(${ASSIMP_INCLUDE_PATH})
include_directories(${OVR_INCLUDE_PATH})
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
			${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/Graphics/GLErrorHandling.cpp
)

add_library(gfk-network STATIC
			${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/Network/UDPSocket.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/Network/IPAddress.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/Network/BytePacker.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/Network/NetworkBuffer.cpp
)

add_library(gfk-system STATIC
			${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/System/GameTime.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/System/Logger.cpp
)

add_library(gfk STATIC
			${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/Game.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/ConsoleGame.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/Components/GameObject.cpp
)

target_link_libraries(gfk-network gfk-system)

if (WIN32)
	target_link_libraries(gfk-graphics OpenGL32)
endif ()

target_link_libraries(gfk-graphics ${GLEW_LIBRARY} ${GLFW_LIBRARY} ${ASSIMP_LIBRARY} gfk-system gfk-math)
target_link_libraries(gfk-input gfk-math gfk-system)

if (NOT WIN32 AND NOT APPLE)
	target_link_libraries(gfk-math ${UUID_LIBRARY} gfk-system)
endif ()

target_link_libraries(gfk gfk-math gfk-input gfk-graphics gfk-network gfk-system)

add_subdirectory(test)
