add_executable(server ServerTest.cpp)
target_link_libraries(server gfk-network)

add_executable(udpServer UDPServerTest.cpp)
target_link_libraries(udpServer gfk-network)
