Shader "SimpleSky"
{
    Properties
    {
        [NoScaleOffset] _MainTex("BaseColor Map", 2D) = "skybox" {}
    }

    Category
    {
        Kernel
        {
            Tags {"Name" = "SimpleSky", "Type" = "Graphics"}

            ZWrite Off ZTest LEqual Cull Front
            ColorMask RGB

            HLSLPROGRAM
            #include "../../Assets/Shader/Common.hlsl"

            struct VertexIn
            {
                float3 posL : POSITION;
                float3 normalL : NORMAL;
                float2 texC : TEXCOORD0;
            };

            struct VertexOut
            {
                float4 posH : SV_POSITION;
                float3 posL : POSITION;
            };

            VertexOut VS(VertexIn In)
            {
                VertexOut Out;

                // Use local vertex position as cubemap lookup vector.
                Out.posL = In.posL;

                // Transform to world space.
                float4 posW = float4(In.posL, 1.0f);

                // Always center sky about camera.
                posW.xyz += gEyePosW;

                // Set z = w so that z/w = 1 (i.e., skydome always on far plane).
                Out.posH = mul(gViewProj, posW).xyww;

                return Out;
            }

            float4 PS(VertexOut In) : SV_Target
            {
                return gCubeMap.Sample(gsamLinearWrap, In.posL);
            }
            ENDHLSL
        }
    }
}