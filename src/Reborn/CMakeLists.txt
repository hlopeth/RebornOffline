project(Reborn VERSION 0.1.0)

include_directories(${SDL2_SOURCE_DIR}/include ${CMAKE_BINARY_DIR}/include)

add_library(Reborn "Reborn.h" "Reborn.cpp" "Application.h" "Application.cpp" "EntryPoint.h" "Core.h" "Core.cpp")
target_link_libraries(Reborn SDL2)