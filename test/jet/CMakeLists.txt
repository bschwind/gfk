include_directories(include)

add_executable(jet
				Main.cpp
				JetGame.cpp
				objects/Jet.cpp
				objects/ClientData.cpp
				objects/GameInput.cpp
				network/NetworkHelper.cpp
				network/Packet.cpp
				network/Outbox.cpp
				network/JetClient.cpp
				JetCamera.cpp)
target_link_libraries(jet gfk)
file(COPY assets DESTINATION .)

add_subdirectory(server)
