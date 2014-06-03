add_executable(client ClientTest.cpp)
target_link_libraries(client gfk-network)

add_executable(server ServerTest.cpp)
target_link_libraries(server gfk-network)

add_executable(udpServer UDPServerTest.cpp)
target_link_libraries(udpServer gfk-network)

add_executable(bytePackerTest BytePackerTest.cpp)
target_link_libraries(bytePackerTest gfk-network)
