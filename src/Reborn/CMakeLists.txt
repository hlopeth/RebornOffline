 add_subdirectory(thirdParty)
project(Reborn VERSION 0.1.0)

include_directories(${SDL2_SOURCE_DIR}/include ${CMAKE_BINARY_DIR}/include)
set(ELPP_SOURCE_DIR thirdParty/easyloggingpp)
set(IMGUI_SOURCE_DIR thirdParty/imgui)
set(ASSIMP_SOURCE_DIR thirdParty/assimp-5.0.1/include)
include_directories(${IMGUI_SOURCE_DIR})
include_directories(${GLAD_SOURCE_DIR})
include_directories(${ASSIMP_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})


set(REBORN_GRAPHICS_PLATFORM "OpenGL")

if(REBORN_GRAPHICS_PLATFORM MATCHES "OpenGL")
	find_package(OpenGL REQUIRED)
	add_compile_definitions(REBORN_OPENGL)
	set(GRAPHICS_PLATFORM_SOURCES
		"Graphics/Platform/OpenGL/GLRenderer.cpp" 
	)
else()
	MESSAGE_ERROR("aaaa")
endif()

set(SOURCE_FILES
	"Reborn.h"
	"EntryPoint.h"
	"Log.h"
	"Core.h"
	"KeyCodes.h"
	"SDLUtils.h"
	"SDLUtils.cpp"
	"Utils.cpp" 
	 
	"Core/Application.h" 
	"Core/Application.cpp" 
	"Core/ImGuiManager.cpp" 
	"Core/Window.h"  
	"Core/Window.cpp"

	"Graphics/Common/Camera.cpp" 
	"Graphics/Common/Mesh.cpp" 
	"Graphics/Common/VertexAttribute.cpp"
	"Graphics/Common/Transform.cpp"
	"Graphics/Common/Material.cpp"

	"ECS/EntitySystem.h" 
	"Components/Transform3DComponent.cpp"
	"Components/RenderComponent.cpp"
	 
	"Event/IEvent.h"  
	"Event/EventDispatcher.cpp" 
	"Event/ApplicationShouldCloseEvent.h" 
	"Event/KeyPressedEvent.h" 
	 
	"Resources/ResourceManager.cpp" 
	"Resources/TextResource.cpp" 
	"Resources/ShaderResouce.cpp"
	"Resources/ModelResource.cpp"

	"Math/MathUtils.cpp"

	${ELPP_SOURCE_DIR}/easylogging++.h
	${ELPP_SOURCE_DIR}/easylogging++.cc
	#"Graphics/RendererImpl/RendererGL.cpp"
	#W"Graphics/RendererImpl/RendererStub.cpp"
	#"Graphics/RendererImpl/RendererDirectX11.cpp"
	${GRAPHICS_PLATFORM_SOURCES}
)
 

add_library(Reborn ${SOURCE_FILES})
target_precompile_headers(
	Reborn
	PRIVATE
	<unordered_map>
	<functional>
	<memory>
	<vector>
	<bitset>
	<utility>
	<string>
	<fstream>
	<functional>
)



find_library(D3D11_LIBRARY d3d11.lib     PATHS     "$ENV{DXSDK_DIR}/Lib/x86" "C:/Program Files (x86)/Microsoft DirectX SDK/Lib/x86"     DOC "The directory where d3d11.lib resides")  
find_library(D3DX11_LIBRARY d3dx11.lib     PATHS     "$ENV{DXSDK_DIR}/Lib/x86" "C:/Program Files (x86)/Microsoft DirectX SDK/Lib/x86"     DOC "The directory where d3dx11.lib resides")
#add_compile_definitions(REBORN_DIRECTX11)
target_link_libraries(Reborn ${D3D11_LIBRARY} ${D3DX11_LIBRARY})

target_link_libraries(Reborn ${OPENGL_LIBRARIES})
target_link_libraries(Reborn Glad_lib)
target_link_libraries(Reborn SDL2)
target_link_libraries(Reborn ImGui_lib)
target_link_libraries(Reborn assimp)