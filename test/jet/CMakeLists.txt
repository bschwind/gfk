include_directories(include)

add_executable(jet
				Main.cpp
				JetGame.cpp
				objects/Jet.cpp
				network/NetworkHelper.cpp
				network/Packet.cpp
				JetCamera.cpp)
target_link_libraries(jet gfk)
file(COPY assets DESTINATION .)

add_subdirectory(server)
