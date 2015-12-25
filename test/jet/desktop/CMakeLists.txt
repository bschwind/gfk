set(COMMON_PATH "../common")

include_directories(${COMMON_PATH}/include)

add_executable(jet
				Main.cpp
				JetGame.cpp
				${COMMON_PATH}/objects/Jet.cpp
				${COMMON_PATH}/objects/ClientData.cpp
				${COMMON_PATH}/objects/GameInput.cpp
				${COMMON_PATH}/network/NetworkHelper.cpp
				${COMMON_PATH}/network/Packet.cpp
				${COMMON_PATH}/network/Outbox.cpp
				${COMMON_PATH}/network/JetClient.cpp
				${COMMON_PATH}/JetCamera.cpp
				${COMMON_PATH}/TopDownCamera.cpp)
target_link_libraries(jet gfk)
file(COPY assets DESTINATION .)
