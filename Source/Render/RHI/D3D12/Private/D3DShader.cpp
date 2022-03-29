#include "Render/RHI/D3D12/Public/D3DShader.h"

using namespace Lumen::Render;

D3DShader::D3DShader(std::string_view hlsl)
{
    vertexShader = CompileShader(hlsl, nullptr, "VS", "vs_5_1");
    pixelShader = CompileShader(hlsl, nullptr, "PS", "ps_5_1");
}

Microsoft::WRL::ComPtr<ID3DBlob> D3DShader::CompileShader(std::string_view hlsl, const D3D_SHADER_MACRO* defines, std::string_view entryPoint, std::string_view target)
{
    UINT compileFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)  
    compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

    Microsoft::WRL::ComPtr<ID3DBlob> errors;
    Microsoft::WRL::ComPtr<ID3DBlob> byteCode = nullptr;
    HRESULT hr = S_OK;
    hr = D3DCompile(hlsl.data(), hlsl.size(), NULL, defines, D3D_COMPILE_STANDARD_FILE_INCLUDE, entryPoint.data(),
        target.data(), compileFlags, 0, &byteCode, &errors);

    if (errors != nullptr)
        OutputDebugStringA((char*)errors->GetBufferPointer());

    ThrowIfFailed(hr);

    return byteCode;
}