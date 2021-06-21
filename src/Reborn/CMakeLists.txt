project(Reborn VERSION 0.1.0)

include_directories(${SDL2_SOURCE_DIR}/include ${CMAKE_BINARY_DIR}/include)
include_directories(${ELPP_SOURCE_DIR})

set(SOURCE_FILES
	"Reborn.h"
	"Reborn.cpp" 
	"Application.h"
	"Application.cpp" 
	"EntryPoint.h"
	"System.h" 
	"System.cpp" 
	"Event/Event.h"  
	"Event/EventHandlerBase.h" 
	"Event/EventHandlerBase.cpp" 
	"Event/EventHandler.h" 
	"Window.h"  
	"Window.cpp"
	${ELPP_SOURCE_DIR}/easylogging++.h
	${ELPP_SOURCE_DIR}/easylogging++.cc
)

add_library(Reborn ${SOURCE_FILES} )
target_link_libraries(Reborn SDL2)