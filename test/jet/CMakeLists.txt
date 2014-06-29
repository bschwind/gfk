add_executable(jet
				Main.cpp
				JetGame.cpp)
target_link_libraries(jet gfk)
file(COPY assets DESTINATION .)
