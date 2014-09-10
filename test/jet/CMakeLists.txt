include_directories(include)

add_executable(jet
				Main.cpp
				JetGame.cpp
				Packets.cpp
				objects/Jet.cpp
				network/RemoteConnection.cpp
				network/Packet.cpp
				JetCamera.cpp)
target_link_libraries(jet gfk)
file(COPY assets DESTINATION .)

add_subdirectory(server)
