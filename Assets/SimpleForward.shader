Shader "SimpleForward"
{
    Properties
    {
        [NoScaleOffset] _MainTex("BaseColor Map", 2D) = "../../Assets/boxBaseColor.png" {}
    }

    Category
    {
        Kernel
        {
            Tags {"Name" = "SimpleForward", "Type" = "Graphics"}

            ZWrite On ZTest LEqual Cull Back
            ColorMask RGB

            HLSLPROGRAM
            #include "../../Assets/Common.hlsl"

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
                float4 posw = float4(In.posL, 1.0);
                Out.posW = posw.xyz;
                Out.posH = mul(gViewProj, posw);
                Out.normalW = normalize(In.normalL);
                return Out;
            }

            float4 PS(VertexOut In) : SV_Target
            {
                Material mat;
                mat.DiffuseAlbedo = float4(1.0, 1.0, 1.0, 1.0);
                mat.Shininess = 0.6;
                mat.FresnelR0 = float3(0.01, 0.01, 0.01);

                float4 diffuse = gTextureMaps[0].Sample(gsamAnisotropicWrap, In.texC);

                float3 toEyeW = normalize(gEyePosW - In.posW);

                float3 directLight = ComputeDirectionalLight(gLights[0], mat, In.normalW, toEyeW);
                
                return float4(diffuse * directLight, 1.0);
            }
            ENDHLSL
        }
    }
}