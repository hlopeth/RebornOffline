project(Reborn VERSION 0.1.0)

include_directories(${SDL2_SOURCE_DIR}/include ${CMAKE_BINARY_DIR}/include)

add_library(Reborn "Reborn.h" "Reborn.cpp" "Application.h" "Application.cpp" "EntryPoint.h" "System.h" "System.cpp" "Event/Event.h"  "Event/EventHandlerBase.h" "Event/EventHandlerBase.cpp" "Event/EventHandler.h" "Window.h"  "Window.cpp")
target_link_libraries(Reborn SDL2)