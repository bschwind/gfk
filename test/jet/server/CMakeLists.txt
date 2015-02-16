add_executable(jetServer
				JetServer.cpp
				../network/NetworkHelper.cpp
				../network/Packet.cpp
				../objects/Jet.cpp
				../objects/ClientData.cpp)
target_link_libraries(jetServer gfk)
