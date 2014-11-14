#
# Try to find GLEW library and include path.
# Once done this will define
#
# UUID_FOUND
# UUID_INCLUDE_PATH
# UUID_LIBRARY
# 

FIND_LIBRARY( UUID_LIBRARY
	NAMES uuid libossp-uuid++
	PATHS
	/usr/lib64
	/usr/lib
	/usr/local/lib64
	/usr/local/lib
	/sw/lib
	/opt/local/lib
	DOC "The UUID library")

SET(UUID_FOUND "NO")
IF (UUID_INCLUDE_PATH AND UUID_LIBRARY)
	SET(UUID_LIBRARIES ${UUID_LIBRARY})
	SET(UUID_FOUND "YES")
ENDIF (UUID_INCLUDE_PATH AND UUID_LIBRARY)


include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(UUID DEFAULT_MSG UUID_LIBRARY UUID_INCLUDE_PATH)
