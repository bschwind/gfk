add_executable(basic-window-test BasicWindowTest.cpp)
target_link_libraries(basic-window-test gfk)

add_executable(easing EasingTest.cpp)
target_link_libraries(easing gfk)

add_executable(guid-test GUIDTest.cpp)
target_link_libraries(guid-test gfk-math gfk-system)

add_executable(data-size DataTypeSizes.cpp)
target_link_libraries(data-size gfk-system)
