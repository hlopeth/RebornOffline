project(Editor VERSION 0.1.0)

include_directories(../Reborn)
add_executable(Editor main.cpp)
target_link_libraries(Editor Reborn)