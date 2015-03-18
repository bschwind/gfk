cmake_minimum_required(VERSION 2.8)
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.7" CACHE STRING "The minimum version of OS X to support")
if (APPLE)
	if (CMAKE_OSX_DEPLOYMENT_TARGET)
		set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mmacosx-version-min=${CMAKE_OSX_DEPLOYMENT_TARGET} " CACHE STRING "Set the min OS X version in the linker flags")
	endif()
endif()
project(GFK C CXX)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
set(CMAKE_DEBUG_POSTFIX d)

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	set(LINUX TRUE)
else()
	set(LINUX FALSE)
endif()

# Options

option(64-BIT "Build 64-bit binary" ON)

if (APPLE)
	option(BUILD_FAT_BINARY "Build a universal (fat) binary" ON)
endif()

option(BUILD_SHARED_LIBRARY "Build a shared library" OFF)
option(BUILD_STATIC_LIBRARY "Build a static library" ON)

# Actually use the options here
if (${64-BIT})
	if (APPLE)
		set(CMAKE_OSX_ARCHITECTURES x86_64)
	endif()

	if(${LINUX})
		#set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} -m64)
		#set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -m64)
	endif()
else()
	if (APPLE)
		set(CMAKE_OSX_ARCHITECTURES i386)
	endif()

	if(${LINUX})
		#set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} -m32)
		#set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -m32)
	endif()
endif()

if (${BUILD_FAT_BINARY})
	set(CMAKE_OSX_ARCHITECTURES i386;x86_64)
endif()

# Compiler-specific C++11 activation.
if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x ")
elseif ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++ ")
endif ()

# Enable all warnings
add_definitions(-Wall -DGLEW_STATIC)

# Set up external libraries
add_subdirectory(lib/glew)
add_subdirectory(lib/glfw)
add_subdirectory(lib/assimp)
add_subdirectory(lib/enet)
add_subdirectory(lib/net_adapter)
find_package(OVR)

# Link against libuuid for Linux
if (NOT WIN32 AND NOT APPLE)
	find_package(UUID)
endif ()

# Add header paths
include_directories(lib/glew/include)
include_directories(lib/glfw/include)
include_directories(lib/assimp/include)
include_directories(lib/enet/include)
include_directories(lib/net_adapter/include)
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
			${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/Graphics/RenderTarget2D.cpp
)

add_library(gfk-vr STATIC
			${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/VR/VRCamera.cpp
)

add_library(gfk-network STATIC
			${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/Network/UDPSocket.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/Network/IPAddress.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/Network/BytePacker.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/Network/NetworkBuffer.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/Network/NetDiscoveryServer.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/src/GFK/Network/NetDiscoveryClient.cpp
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

target_link_libraries(gfk-network gfk-system gfk-math enet net_adapter_static)

if (WIN32)
	target_link_libraries(gfk-graphics OpenGL32)
endif ()

target_link_libraries(gfk-graphics glew_static glfw ${GLFW_LIBRARIES} assimp gfk-system gfk-math)
target_link_libraries(gfk-vr gfk-graphics ${OVR_LIBRARY})
target_link_libraries(gfk-input gfk-math gfk-system)

if (NOT WIN32 AND NOT APPLE)
	target_link_libraries(gfk-math ${UUID_LIBRARY} gfk-system)
endif ()

target_link_libraries(gfk gfk-math gfk-input gfk-graphics gfk-network gfk-system gfk-vr)

add_subdirectory(test)
