project(Editor VERSION 0.1.0)

include_directories(../Reborn)
include_directories(${IMGUI_SOURCE_DIR})
add_executable(Editor main.cpp)
target_link_libraries(Editor Reborn)