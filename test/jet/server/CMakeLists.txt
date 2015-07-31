set(COMMON_PATH "../common")

include_directories(${COMMON_PATH}/include)

add_executable(jetServer
				JetServer.cpp
				${COMMON_PATH}/network/NetworkHelper.cpp
				${COMMON_PATH}/network/Packet.cpp
				${COMMON_PATH}/network/Outbox.cpp
				${COMMON_PATH}/objects/Jet.cpp
				${COMMON_PATH}/objects/ClientData.cpp
				${COMMON_PATH}/objects/GameInput.cpp)
target_link_libraries(jetServer gfk)
