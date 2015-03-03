#
# Try to find OVR library and include path.
# Once done this will define
#
# OVR_FOUND
# OVR_INCLUDE_PATH
# OVR_LIBRARY

FIND_PATH(OVR_INCLUDE_PATH
	NAMES OVR.h OVR_Kernel.h OVR_Version.h
	PATHS ${PROJECT_SOURCE_DIR}/lib/ovr/include/
)

FIND_LIBRARY(OVR_LIBRARY
	NAMES
		libovr.a # OS X
		libovr.lib # Windows 32-bit
		libovr64.lib # Windows 64-bit
	PATHS
		${PROJECT_SOURCE_DIR}/lib/ovr/osx/

		# Yay Windows permutations
		# TODO - Auto-detect the correct one here. Currently you have
		#        to move the desired version to the top of this list
		${PROJECT_SOURCE_DIR}/lib/ovr/windows/lib/Win32/VS2010/
		${PROJECT_SOURCE_DIR}/lib/ovr/windows/lib/Win32/VS2012/
		${PROJECT_SOURCE_DIR}/lib/ovr/windows/lib/Win32/VS2013/
		${PROJECT_SOURCE_DIR}/lib/ovr/windows/lib/x64/VS2010/
		${PROJECT_SOURCE_DIR}/lib/ovr/windows/lib/x64/VS2012/
		${PROJECT_SOURCE_DIR}/lib/ovr/windows/lib/x64/VS2013/
)

SET(OVR_FOUND "NO")
IF (OVR_INCLUDE_PATH AND OVR_LIBRARY)
	SET(OVR_INCLUDE_PATH ${OVR_INCLUDE_PATH})
	SET(OVR_LIBRARY ${OVR_LIBRARY})
	SET(OVR_FOUND "YES")
ENDIF (OVR_INCLUDE_PATH AND OVR_LIBRARY)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(OVR DEFAULT_MSG OVR_LIBRARY OVR_INCLUDE_PATH)
