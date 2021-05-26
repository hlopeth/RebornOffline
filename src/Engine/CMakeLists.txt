project(engine VERSION 0.1.0)

include_directories(${SDL2_SOURCE_DIR}/include ${CMAKE_BINARY_DIR}/include)

add_library(engine engine.cpp)
target_link_libraries(engine SDL2)