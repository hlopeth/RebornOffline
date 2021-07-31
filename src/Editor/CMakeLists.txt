project(Editor VERSION 0.1.0)

include_directories(../Reborn)
include_directories(${IMGUI_SOURCE_DIR})
add_executable(Editor main.cpp)
target_link_libraries(Editor Reborn)

add_compile_definitions(ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/Assets")