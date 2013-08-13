find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

add_executable(server main.cpp)
target_link_libraries(server gfk ${OPENGL_LIBRARIES})
