add_executable(jetServer
				JetServer.cpp
				../network/RemoteConnection.cpp
				../network/Packet.cpp)
target_link_libraries(jetServer gfk)
