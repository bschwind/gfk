add_executable(client ClientTest.cpp)
target_link_libraries(client gfk)

add_executable(server ServerTest.cpp)
target_link_libraries(server gfk-network)

add_executable(bytePackerTest BytePackerTest.cpp)
target_link_libraries(bytePackerTest gfk-network)

add_executable(networkBufferTest NetworkBufferTest.cpp)
target_link_libraries(networkBufferTest gfk-network)

add_executable(netDiscoveryClient NetDiscoveryClientTest.cpp)
target_link_libraries(netDiscoveryClient gfk-network)
