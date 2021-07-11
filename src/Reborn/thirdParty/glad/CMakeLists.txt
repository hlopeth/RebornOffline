project(GLAD C)

set(GLAD_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(Glad_lib "glad.c")