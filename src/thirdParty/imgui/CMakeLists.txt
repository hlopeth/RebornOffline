project(ImGui VERSION 0.1.0)
set(IMGUI_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)
find_package(OpenGL REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${SDL2_SOURCE_DIR}/include ${CMAKE_BINARY_DIR}/include)
include_directories(${GLAD_SOURCE_DIR})
set(SOURCE_FILES
    "imgui.cpp"
    "imgui_demo.cpp"
    "imgui_draw.cpp"
    "imgui_tables.cpp"
    "imgui_widgets.cpp"

    "backends/imgui_impl_opengl3.cpp"
    "backends/imgui_impl_sdl.cpp"
)

add_library(ImGui_lib ${SOURCE_FILES} )
target_link_libraries(ImGui_lib ${OPENGL_LIBRARIES})
target_link_libraries(ImGui_lib Glad_lib)
