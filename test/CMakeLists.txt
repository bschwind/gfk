#Why do I have to include OpenGL here? Doesn't SFML take care of that?

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

add_executable(test main.cpp)
target_link_libraries(test gfk ${OPENGL_LIBRARIES})
