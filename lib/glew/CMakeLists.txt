cmake_minimum_required(VERSION 2.8)
project(GLEW)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)

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
		set(CFLAGS ${CFLAGS} -m64)
		set(CXXFLAGS ${CFLAGS} -m64)
	endif()
else()
	if (APPLE)
		set(CMAKE_OSX_ARCHITECTURES i386)
	endif()

	if(${LINUX})
		set(CFLAGS ${CFLAGS} -m32)
		set(CXXFLAGS ${CFLAGS} -m32)
	endif()
endif()

if(${BUILD_FAT_BINARY})
	set(CMAKE_OSX_ARCHITECTURES i386;x86_64)
endif()

# Compiler-specific C++11 activation.
if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
	set(CMAKE_CXX_FLAGS "-std=c++0x")
elseif ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
	#set(CMAKE_CXX_FLAGS "-stdlib=libc++ -std=c++11")
	#set(CMAKE_C_FLAGS "-stdlib=libc++")
endif ()

# External Libraries
if(WIN32)
	set(GL_LIBRARY opengl32)
elseif(APPLE)
	find_library(GL_LIBRARY OpenGL)
	find_library(AGL_LIBRARY AGL)
	set(PLATFORM_SPECIFIC_LIBRARIES ${AGL_LIBRARY})
else()
	set(GL_LIBRARY GL)
	set(PLATFORM_SPECIFIC_LIBRARIES X11 dl Xext)
endif()

# Enable all warnings
add_definitions(-Wall)

# Add header paths
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Add the subdirectories
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

set(GLEW_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/glew.c)

if (${BUILD_SHARED_LIBRARY})
	if(WIN32)
		add_definitions(-DGLEW_BUILD)
	endif()

	add_library(glew_shared SHARED ${GLEW_SRC_FILES})
	SET_PROPERTY( TARGET glew_shared PROPERTY DEBUG_POSTFIX d )
	TARGET_LINK_LIBRARIES( glew_shared ${GL_LIBRARY} ${PLATFORM_SPECIFIC_LIBRARIES} )
endif()

if(${BUILD_STATIC_LIBRARY})
	if(WIN32)
		add_definitions(-DGLEW_STATIC)
	endif()

	add_library(glew_static STATIC ${GLEW_SRC_FILES})
	SET_PROPERTY( TARGET glew_static PROPERTY DEBUG_POSTFIX d )
	TARGET_LINK_LIBRARIES( glew_static ${GL_LIBRARY} ${PLATFORM_SPECIFIC_LIBRARIES} )
endif()
