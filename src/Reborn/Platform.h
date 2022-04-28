#pragma once
#ifdef REBORN_OPENGL
#include <SDL_opengl.h>
#else
#ifdef REBORN_DIRECTX11
#include <windows.h>
#include <d3d11_1.h>
#endif // REBORN_DIRECTX11
#endif // REBORN_OPENGL

#include "Graphics/Common/APIType.h"

#ifdef REBORN_OPENGL

	typedef void *RenderingContext;
	typedef GLfloat FloatValue;
	typedef GLint IntValue;
	typedef GLuint UIntValue;
	typedef GLenum EnumValue;
	typedef GLsizei SizeiValue;
	typedef GLchar CharValue;

#define API_TYPE Reborn::APIType::OpenGL
#define REBORN_STATIC_DRAW GL_STATIC_DRAW
#define REBORN_TEXTURE_2D GL_TEXTURE_2D
#define REBORN_RENDERBUFFER GL_RENDERBUFFER
#define REBORN_COLOR_ATTACHMENT0 GL_COLOR_ATTACHMENT0
#define REBORN_COLOR_ATTACHMENT1 GL_COLOR_ATTACHMENT1
#define REBORN_COLOR_ATTACHMENT2 GL_COLOR_ATTACHMENT2
#define REBORN_DEPTH_STENCIL_ATTACHMENT GL_DEPTH_STENCIL_ATTACHMENT

#define REBORN_ARRAY_BUFFER GL_ARRAY_BUFFER
#define REBORN_ELEMENT_ARRAY_BUFFER GL_ELEMENT_ARRAY_BUFFER

#define REBORN_FLOAT GL_FLOAT


#else
#ifdef REBORN_DIRECTX11
struct RenderingContext {
	ID3D11DeviceContext* pDeviceContext;
	ID3D11Device* pDevice;
	IDXGISwapChain* pSwapChain;
};

typedef FLOAT FloatValue;
typedef INT IntValue;
typedef UINT UIntValue;
typedef unsigned int EnumValue;
typedef int SizeiValue;
typedef CHAR CharValue;

#define API_TYPE Reborn::APIType::DirectX11
#define REBORN_STATIC_DRAW 1
#define REBORN_TEXTURE_2D 2
#define REBORN_RENDERBUFFER 3
#define REBORN_COLOR_ATTACHMENT0 4
#define REBORN_COLOR_ATTACHMENT1 5
#define REBORN_COLOR_ATTACHMENT2 6
#define REBORN_DEPTH_STENCIL_ATTACHMENT 7

#define REBORN_ARRAY_BUFFER 8
#define REBORN_ELEMENT_ARRAY_BUFFER 9

#define REBORN_FLOAT 10

#else
	typedef int RenderingContext;
	typedef float FloatValue;
	typedef int IntValue;
	typedef unsigned int UIntValue;
	typedef unsigned int EnumValue;
	typedef int SizeiValue;
	typedef char CharValue;

#define API_TYPE Reborn::APIType::NONE
#define REBORN_STATIC_DRAW 1
#define REBORN_TEXTURE_2D 2
#define REBORN_RENDERBUFFER 3
#define REBORN_COLOR_ATTACHMENT0 4
#define REBORN_COLOR_ATTACHMENT1 5
#define REBORN_COLOR_ATTACHMENT2 6
#define REBORN_DEPTH_STENCIL_ATTACHMENT 7

#define REBORN_ARRAY_BUFFER 8
#define REBORN_ELEMENT_ARRAY_BUFFER 9

#define REBORN_FLOAT 10
#endif //REBORN_DIRECT11
#endif  //REBORN_OPENGL