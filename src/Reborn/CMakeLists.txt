project(Reborn VERSION 0.1.0)

include_directories(${SDL2_SOURCE_DIR}/include ${CMAKE_BINARY_DIR}/include)
include_directories(${ELPP_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCE_FILES
	"Reborn.h"
	 
	"Application.h"
	"Application.cpp" 
	"EntryPoint.h"
	"System.h" 
	"System.cpp" 
	"Event/IEvent.h"  
	 
	 
	"IEventHandler.h" 
	"Window.h"  
	"Window.cpp"
	${ELPP_SOURCE_DIR}/easylogging++.h
	${ELPP_SOURCE_DIR}/easylogging++.cc
	"Event/EventDispatcher.cpp" 
	"Event/ApplicationCloseEvent.h" 
	"IEventHandler.h"
	"Log.h"
 )

add_library(Reborn ${SOURCE_FILES})
target_link_libraries(Reborn SDL2)