#pragma once
#include "Platform.h"
#include "Graphics/Common/ShaderProgram.h"

namespace Reborn
{
    class D11ShaderProgram: public ShaderProgram
    {
    public:
        D11ShaderProgram(): ShaderProgram(API_TYPE) {};
        D11ShaderProgram(
            ID3D11VertexShader* _pVertexShader, 
            ID3D11PixelShader* _pPixelShader
        ):
         ShaderProgram(API_TYPE),
         pVertexShader(_pVertexShader),
         pPixelShader(_pPixelShader)
        {}
        
        ID3D11VertexShader* pVertexShader = nullptr;
        ID3D11PixelShader* pPixelShader = nullptr;
    }
}