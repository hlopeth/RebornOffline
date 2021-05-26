project(game VERSION 0.1.0)

include_directories(../Engine)
add_executable(game main.cpp)
target_link_libraries(game engine)