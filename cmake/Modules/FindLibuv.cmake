# Find the include directory
find_path(LIBUV_INCLUDE_PATH
	uv.h
	PATHS
	/usr/include
	/usr/local/include	
)

mark_as_advanced(LIBUV_INCLUDE_PATH)

# Find the library directory
find_library(LIBUV_LIBRARY
	NAMES uv libuv
	PATHS
	/usr/lib
	/usr/local/lib
)

mark_as_advanced(LIBUV_LIBRARY)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(Libuv DEFAULT_MSG
	LIBUV_LIBRARY LIBUV_INCLUDE_PATH)

if(LIBUV_FOUND)
	set(LIBUV_INCLUDE_DIRS ${LIBUV_INCLUDE_PATH})
endif()
