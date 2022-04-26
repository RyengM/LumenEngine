#pragma once

#include <string>

// Refer to Infinity Engine

namespace Lumen::Render
{
    enum class EUsageType : uint32_t
    {
        Default                     = 1,
        DepthStencil                = 2,
        RenderTarget                = 4,
        UnorderedAccess             = 8
    };

    enum class EStorageType : uint32_t
    {
        UMA                         = 0x1,
        Static                      = 0x2,
        Dynamic                     = 0x4,
        Staging                     = 0x8,
        Default                     = 0x10
    };

    enum class EBufferType : uint32_t
    {
        Index                       = 0,
        Vertex                      = 1,
        Append                      = 2,
        Consume                     = 3,
        Counter                     = 4,
        Constant                    = 5,
        Argument                    = 6,
        Structured                  = 7,
        ByteAddress                 = 8
    };

    enum class ETextureType : uint32_t
    {
        Tex2D                       = 0,
        Tex2DArray                  = 1,
        Tex2DSparse                 = 2,
        TexCube                     = 3,
        TexCubeArray                = 4,
        Tex3D                       = 5,
        Tex3DSparse                 = 6,
    };

    enum class EResourceType : uint32_t
    {
        Buffer                      = 0,
        Texture                     = 1
    };

    enum class EDepthBits : uint32_t
    {
        None                        = 0,
        Depth8                      = 8,
        Depth16                     = 16,
        Depth24                     = 24,
        Depth32                     = 32
    };

    enum class EWrapMode : uint32_t
    {
        Clamp                       = 0,
        Border                      = 1,
        Repeat                      = 2,
        Mirror                      = 3,
        MirrorOnce                  = 4
    };
    
    enum class EFilterMode : uint32_t
    {
        Point                       = 0,
        Bilinear                    = 1,
        Trilinear                   = 2,
        Anisotropic                 = 3
    };

    enum class EMSAASample : uint32_t
    {
        None                        = 1,
        MSAA2x                      = 2,
        MSAA4x                      = 4,
        MSAA8x                      = 8
    };

    enum class EBufferInitState : uint32_t
    {
        Common                      = 0,
        VertexAndConstant           = 0x1,
        GenericRead                 = 0x2,
        CopySrc                     = 0x4,
        CopyDest                    = 0x8
    };

    enum class ETextureInitState : uint32_t
    {
        Common                      = 0,
        RenderTarget                = 0x1,
        Unordered                   = 0x2,
        DepthWrite                  = 0x4,
        DepthRead                   = 0x8,
        PixelShaderResource         = 0x10,
        GenericRead                 = 0x20,
        CopySrc                     = 0x40,
        CopyDest                    = 0x80
    };

    enum class EGraphicsFormat : uint32_t
    {
        None                        = 0,
        R8_SRGB                     = 1,
        R8G8_SRGB                   = 2,
        R8G8B8_SRGB                 = 3,
        R8G8B8A8_SRGB               = 4,
        R8_UNorm                    = 5,
        R8G8_UNorm                  = 6,
        R8G8B8_UNorm                = 7,
        R8G8B8A8_UNorm              = 8,
        R8_SNorm                    = 9,
        R8G8_SNorm                  = 10,
        R8G8B8_SNorm                = 11,
        R8G8B8A8_SNorm              = 12,
        R8_UInt                     = 13,
        R8G8_UInt                   = 14,
        R8G8B8_UInt                 = 15,
        R8G8B8A8_UInt               = 16,
        R8_SInt                     = 17,
        R8G8_SInt                   = 18,
        R8G8B8_SInt                 = 19,
        R8G8B8A8_SInt               = 20,
        R16_UNorm                   = 21,
        R16G16_UNorm                = 22,
        R16G16B16_UNorm             = 23,
        R16G16B16A16_UNorm          = 24,
        R16_SNorm                   = 25,
        R16G16_SNorm                = 26,
        R16G16B16_SNorm             = 27,
        R16G16B16A16_SNorm          = 28,
        R16_UInt                    = 29,
        R16G16_UInt                 = 30,
        R16G16B16_UInt              = 31,
        R16G16B16A16_UInt           = 32,
        R16_SInt                    = 33,
        R16G16_SInt                 = 34,
        R16G16B16_SInt              = 35,
        R16G16B16A16_SInt           = 36,
        R32_UInt                    = 37,
        R32G32_UInt                 = 38,
        R32G32B32_UInt              = 39,
        R32G32B32A32_UInt           = 40,
        R32_SInt                    = 41,
        R32G32_SInt                 = 42,
        R32G32B32_SInt              = 43,
        R32G32B32A32_SInt           = 44,
        R16_SFloat                  = 45,
        R16G16_SFloat               = 46,
        R16G16B16_SFloat            = 47,
        R16G16B16A16_SFloat         = 48,
        R32_SFloat                  = 49,
        R32G32_SFloat               = 50,
        R32G32B32_SFloat            = 51,
        R32G32B32A32_SFloat         = 52,
        B8G8R8_SRGB                 = 56,
        B8G8R8A8_SRGB               = 57,
        B8G8R8_UNorm                = 58,
        B8G8R8A8_UNorm              = 59,
        B8G8R8_SNorm                = 60,
        B8G8R8A8_SNorm              = 61,
        B8G8R8_UInt                 = 62,
        B8G8R8A8_UInt               = 63,
        B8G8R8_SInt                 = 64,
        B8G8R8A8_SInt               = 65,
        R4G4B4A4_UNormPack16        = 66,
        B4G4R4A4_UNormPack16        = 67,
        R5G6B5_UNormPack16          = 68,
        B5G6R5_UNormPack16          = 69,
        R5G5B5A1_UNormPack16        = 70,
        B5G5R5A1_UNormPack16        = 71,
        A1R5G5B5_UNormPack16        = 72,
        E5B9G9R9_UFloatPack32       = 73,
        B10G11R11_UFloatPack32      = 74,
        A2B10G10R10_UNormPack32     = 75,
        A2B10G10R10_UIntPack32      = 76,
        A2B10G10R10_SIntPack32      = 77,
        A2R10G10B10_UNormPack32     = 78,
        A2R10G10B10_UIntPack32      = 79,
        A2R10G10B10_SIntPack32      = 80,
        RGB_DXT1_SRGB               = 96,
        RGBA_DXT1_SRGB              = 96,
        RGB_DXT1_UNorm              = 97,
        RGBA_DXT1_UNorm             = 97,
        RGBA_DXT3_SRGB              = 98,
        RGBA_DXT3_UNorm             = 99,
        RGBA_DXT5_SRGB              = 100,
        RGBA_DXT5_UNorm             = 101,
        R_BC4_UNorm                 = 102,
        R_BC4_SNorm                 = 103,
        RG_BC5_UNorm                = 104,
        RG_BC5_SNorm                = 105,
        RGB_BC6H_UFloat             = 106,
        RGB_BC6H_SFloat             = 107,
        RGBA_BC7_SRGB               = 108,
        RGBA_BC7_UNorm              = 109,
        D24_S8_UNorm                = 110,
    };

    // Describe buffer resource
    struct BufferDescriptor
    {
        std::string name;
        size_t count;
        size_t stride;
        EUsageType usageType;
        EBufferType bufferType;
        EStorageType storageType;
        EBufferInitState initState;
    };

    // Describe texture resource
    struct TextureDescriptor
    {
        uint32_t width;
        uint32_t height;
        uint32_t slices;
        bool sparse;
        uint16_t mipLevel;
        uint16_t anisoLevel;
        EMSAASample sample;
        EUsageType usageType;
        ETextureType textureType;
        EStorageType storageType;
        EGraphicsFormat format;
        ETextureInitState initState;
    };

    // Base
    struct RHIResource
    {
        std::string name;
    };

    // Base buffer
    struct RHIBuffer : public RHIResource
    {
        BufferDescriptor descriptor;
    };

    // Base texture
    struct RHITexture : public RHIResource
    {
        TextureDescriptor descriptor;
    };

    // Texture with SRV only
    struct RHIPlainTexture : public RHITexture
    {

    };

    // Texture with SRV and RTV
    struct RHIRenderTarget : public RHITexture
    {

    };

    // Texture with DSV
    struct RHIDepthBuffer : public RHITexture
    {

    };

    // Render target with depth enabled
    struct RHIDepthRenderTarget : public RHITexture
    {

    };

    struct RHIMaterial
    {
    
    };

    struct RHIMeshGeometry : public RHIResource
    {

    };

    struct RHIRenderItem
    {

    };
}