add_subdirectory(thirdParty)
project(Reborn VERSION 0.1.0)
find_package(OpenGL REQUIRED)

include_directories(${SDL2_SOURCE_DIR}/include ${CMAKE_BINARY_DIR}/include)
set(ELPP_SOURCE_DIR thirdParty/easyloggingpp)
set(IMGUI_SOURCE_DIR thirdParty/imgui)
set(ASSIMP_SOURCE_DIR thirdParty/assimp-5.0.1/include)
include_directories(${IMGUI_SOURCE_DIR})
include_directories(${GLAD_SOURCE_DIR})
include_directories(${ASSIMP_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_compile_definitions(-DREBORN_RENDER_BACKEND_OPENGL=1)


set(SOURCE_FILES
	"Core/Application.cpp" 
	"ECS/EntitySystem.h" 
	"Core/Window.cpp"
	#${ELPP_SOURCE_DIR}/easylogging++.h
	${ELPP_SOURCE_DIR}/easylogging++.cc
	"Event/EventDispatcher.cpp" 
	"SDLUtils.cpp"
	"Graphics/Renderer.cpp"
	"Resources/ResourceManager.cpp" 
	"Resources/TextResource.cpp" 
	"Resources/GLSLShaderResouce.cpp"
	"Math/MathUtils.cpp"
	"Graphics/Camera.cpp" 
	"Resources/ModelResource.cpp"
	"Graphics/Mesh.cpp" 
	"Graphics/VertexAttribute.cpp"
	"Components/Transform3DComponent.cpp"
	"Graphics/Transform.cpp"
	"Utils.cpp" 
    "Graphics/Material.cpp" 
	"Graphics/Backends/RenderBackend_GL.cpp" 
	"Graphics/Backends/CommandBuffer.cpp"
	"Graphics/VertexLayout.cpp"
	"Graphics/VertexFactory.cpp")

add_library(Reborn ${SOURCE_FILES} )
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
	<cassert>
)

target_link_libraries(Reborn ${OPENGL_LIBRARIES})
target_link_libraries(Reborn Glad_lib)
target_link_libraries(Reborn SDL2)
target_link_libraries(Reborn ImGui_lib)
target_link_libraries(Reborn assimp)