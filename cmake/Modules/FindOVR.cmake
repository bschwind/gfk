#
# Try to find OVR library and include path.
# Once done this will define
#
# OVR_FOUND
# OVR_INCLUDE_PATH
# OVR_LIBRARY

if (WIN32)
	if (${64-BIT})
		set(WINDOWS_OVR_LIB_NAME "libovr64.lib")

		if (${CMAKE_GENERATOR} MATCHES "Visual Studio 10 2010")
			set(WINDOWS_OVR_PATH ${PROJECT_SOURCE_DIR}/lib/ovr/windows/lib/x64/VS2010/)
		endif()
		if (${CMAKE_GENERATOR} MATCHES "Visual Studio 11 2012")
			set(WINDOWS_OVR_PATH ${PROJECT_SOURCE_DIR}/lib/ovr/windows/lib/x64/VS2012/)
		endif()
		if (${CMAKE_GENERATOR} MATCHES "Visual Studio 12 2013")
			set(WINDOWS_OVR_PATH ${PROJECT_SOURCE_DIR}/lib/ovr/windows/lib/x64/VS2013/)
		endif()
	else()
		set(WINDOWS_OVR_LIB_NAME "libovr.lib")

		if (${CMAKE_GENERATOR} MATCHES "Visual Studio 10 2010")
			set(WINDOWS_OVR_PATH ${PROJECT_SOURCE_DIR}/lib/ovr/windows/lib/Win32/VS2010/)
		endif()
		if (${CMAKE_GENERATOR} MATCHES "Visual Studio 11 2012")
			set(WINDOWS_OVR_PATH ${PROJECT_SOURCE_DIR}/lib/ovr/windows/lib/Win32/VS2012/)
		endif()
		if (${CMAKE_GENERATOR} MATCHES "Visual Studio 12 2013")
			set(WINDOWS_OVR_PATH ${PROJECT_SOURCE_DIR}/lib/ovr/windows/lib/Win32/VS2013/)
		endif()
	endif()
endif()

if (LINUX)
	set(LINUX_OVR_LIB_NAME "libovr.a")
	set(LINUX_OVR_PATH ${PROJECT_SOURCE_DIR}/lib/ovr/linux/release/x86_64/)
endif()

FIND_PATH(OVR_INCLUDE_PATH
	NAMES OVR.h OVR_Kernel.h OVR_Version.h
	PATHS ${PROJECT_SOURCE_DIR}/lib/ovr/include/
)

FIND_LIBRARY(OVR_LIBRARY
	NAMES
		${LINUX_OVR_LIB_NAME} # Linux
		libovr.a # OS X
		${WINDOWS_OVR_LIB_NAME} # Windows
	PATHS
		${LINUX_OVR_PATH}
		${PROJECT_SOURCE_DIR}/lib/ovr/osx/
		${WINDOWS_OVR_PATH}
)

SET(OVR_FOUND "NO")
IF (OVR_INCLUDE_PATH AND OVR_LIBRARY)
	SET(OVR_INCLUDE_PATH ${OVR_INCLUDE_PATH})
	SET(OVR_LIBRARY ${OVR_LIBRARY})
	SET(OVR_FOUND "YES")
ENDIF (OVR_INCLUDE_PATH AND OVR_LIBRARY)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(OVR DEFAULT_MSG OVR_LIBRARY OVR_INCLUDE_PATH)
