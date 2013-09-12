find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

add_executable(basic-window-test BasicWindowTest.cpp)
target_link_libraries(basic-window-test gfk ${OPENGL_LIBRARIES})
