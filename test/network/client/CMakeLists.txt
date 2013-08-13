find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

add_executable(client main.cpp)
target_link_libraries(client gfk ${OPENGL_LIBRARIES})
