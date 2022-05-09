Shader "Default"
{
    Properties
    {
        [NoScaleOffset] _MainTex("BaseColor Map", 2D) = "white" {}
        _Roughness("Roughness", Float) = 0.25
        _FresnelR0("FresnelR0", Color) = (0.01, 0.01, 0.01, 1.0)
        _DiffuseAlbedo("DiffuseAlbedo", Color) = (1.0, 1.0, 1.0, 1.0)
    }

    Category
    {
        Kernel
        {
            Tags {"Name" = "Default", "Type" = "Graphics"}

            ZWrite On ZTest LEqual Cull Back
            ColorMask RGB

            HLSLPROGRAM
            #include "../../Assets/Shader/Common.hlsl"

            cbuffer cbPerMaterial : register(b2)
            {
                float _Roughness;
                float4 _FresnelR0;
                float4 _DiffuseAlbedo;
            }

            struct VertexIn
            {
                float3 posL : POSITION;
                float3 normalL : NORMAL;
                float2 texC : TEXCOORD0;
            };

            struct VertexOut
            {
                float4 posH : SV_POSITION;
                float3 posW : POSITION;
                float3 normalW : NORMAL;
                float2 texC : TEXCOORD0;
            };

            VertexOut VS(VertexIn In)
            {
                VertexOut Out;

                Out.texC = In.texC;
                float4 posw = mul(gWorld, float4(In.posL, 1.0));
                Out.posW = posw.xyz;
                Out.posH = mul(gViewProj, posw);
                Out.normalW = mul((float3x3)gWorld, In.normalL);
                return Out;
            }

            float4 PS(VertexOut In) : SV_Target
            {
                Material mat;
                mat.DiffuseAlbedo = _DiffuseAlbedo;
                mat.Shininess = 1.f - _Roughness;
                mat.FresnelR0 = _FresnelR0;

                In.normalW = normalize(In.normalW);

                float3 toEyeW = normalize(gEyePosW - In.posW);

                float4 diffuse = _DiffuseAlbedo * gTextureMaps[0].Sample(gsamAnisotropicWrap, In.texC);
                float3 directLight = ComputeDirectionalLight(gLights[0], mat, In.normalW, toEyeW);
                float3 litColor = directLight;

                // Specular reflection
                float3 r = reflect(-toEyeW, In.normalW);
                float3 fresnelFactor = SchlickFresnel(_FresnelR0, In.normalW, r);
                litColor += mat.Shininess * fresnelFactor * 0.4;

                return float4(diffuse.xyz * litColor, 1.0);
            }
            ENDHLSL
        }
    }
}