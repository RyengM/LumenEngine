Shader "InfinityPipeline/InfinityLit"
{
	Properties
	{
		[Header(Microface)]
		[NoScaleOffset] _MainTex("BaseColor Map", 2D) = "white" {}

		[TestInt] _Int("TestInt", Int) = 233
		[TestRange] _Range("TestRange", Range(0.0, 1.0)) = 0.7
		[TestColor] _Color("TestColor", Color) = (1.0, 0.2, 0.2, 1.0)
	}

	Category
	{
		Kernel
		{
			Tags {"Name" = "Depth", "Type" = "Graphics"}

			ZWrite On ZTest LEqual Cull Back
			ColorMask RGB

			HLSLPROGRAM
			#pragma vertex Vert
			#pragma fragment Frag

			struct Attributes
			{
				float2 uv0 : TEXCOORD0;
				float4 vertexOS : POSITION;
			};

			struct Varyings
			{
				float2 uv0 : TEXCOORD0;
				float4 vertexCS : SV_POSITION;
			};

			cbuffer PerView
			{
				float4x4 Matrix_ViewProjection;
			};
			cbuffer PerObject
			{
				float4x4 Matrix_ObjectToWorld;
				float4x4 Matrix_WorldToObject;
			};

			#include "../Private/Common.hlsl"

			Varyings Vert(Attributes In)
			{
				Varyings Out = (Varyings)0;

				Out.uv0 = In.uv0;
				float4 WorldPos = mul(Matrix_ObjectToWorld, float4(In.vertexOS.xyz, 1.0));
				Out.vertexCS = mul(Matrix_ViewProjection, WorldPos);
				return Out;
			}

			float4 Frag(Varyings In) : SV_Target
			{
				return 0;
			}
			ENDHLSL
		}

		Kernel
		{
			Tags {"Name" = "GBuffer", "Type" = "Graphics"}
			ZWrite On ZTest LEqual Cull Back

			HLSLPROGRAM
			#pragma vertex Vert
			#pragma fragment Frag

			struct Attributes
			{
				float2 uv0 : TEXCOORD0;
				float3 normalOS : NORMAL;
				float4 vertexOS : POSITION;
			};

			struct Varyings
			{
				float2 uv0 : TEXCOORD0;
				float3 normalWS : TEXCOORD1;
				float4 vertexWS : TEXCOORD2;
				float4 vertexCS : SV_POSITION;
			};

			cbuffer PerView
			{
				float4x4 Matrix_ViewProjection;
			};
			cbuffer PerObject
			{
				float4x4 Matrix_ObjectToWorld;
				float4x4 Matrix_WorldToObject;
			};
			cbuffer PerMaterial
			{
				float _SpecularLevel;
				float4 _BaseColor;
			};
			Texture2D _MainTex;
			SamplerState sampler_MainTex;

			#include "../Private/Common.hlsl"

			Varyings Vert(Attributes In)
			{
				Varyings Out = (Varyings)0;

				Out.uv0 = In.uv0;
				Out.normalWS = normalize(mul((float3x3)Matrix_ObjectToWorld, In.normalOS));
				Out.vertexWS = mul(Matrix_ObjectToWorld, float4(In.vertexOS.xyz, 1.0));
				Out.vertexCS = mul(Matrix_ViewProjection, Out.vertexWS);
				return Out;
			}

			void Frag(Varyings In, out float4 GBufferA : SV_Target0, out float4 GBufferB : SV_Target1)
			{
				float3 BaseColor = _MainTex.Sample(sampler_MainTex, In.uv0).rgb;

				GBufferA = float4(BaseColor, 1);
				GBufferB = float4((In.normalWS * 0.5 + 0.5), 1);
			}
			ENDHLSL
		}

		Kernel
		{
			Tags {"Name" = "Forward", "Type" = "Graphics"}
			ZWrite Off ZTest Equal Cull Back

			HLSLPROGRAM
			#pragma vertex Vert
			#pragma fragment Frag

			struct Attributes
			{
				float2 uv0 : TEXCOORD0;
				float3 normalOS : NORMAL;
				float4 vertexOS : POSITION;
			};

			struct Varyings
			{
				float2 uv0 : TEXCOORD0;
				float3 normalWS : TEXCOORD1;
				float4 vertexWS : TEXCOORD2;
				float4 vertexCS : SV_POSITION;
			};

			cbuffer PerView
			{
				float4x4 Matrix_ViewProjection;
			};
			cbuffer PerObject
			{
				float4x4 Matrix_ObjectToWorld;
				float4x4 Matrix_WorldToObject;
			};
			cbuffer PerMaterial
			{
				float _SpecularLevel;
				float4 _BaseColor;
			};
			Texture2D _MainTex;
			SamplerState sampler_MainTex;

			#include "../Private/Common.hlsl"

			Varyings Vert(Attributes In)
			{
				Varyings Out = (Varyings)0;

				Out.uv0 = In.uv0;
				Out.normal = normalize(mul((float3x3)Matrix_ObjectToWorld, In.normalOS));
				Out.vertexWS = mul(Matrix_ObjectToWorld, float4(In.vertexOS.xyz, 1.0));
				Out.vertexCS = mul(Matrix_ViewProjection, Out.vertexWS);
				return Out;
			}

			void Frag(Varyings In, out float4 Diffuse : SV_Target0, out float4 Specular : SV_Target1)
			{
				float3 worldPos = In.vertexWS.xyz;
				float3 BaseColor = _MainTex.Sample(sampler_MainTex, In.uv).rgb;

				Diffuse = float4(BaseColor, 1);
				Specular = float4(BaseColor, 1);
			}
			ENDHLSL
		}

		Kernel
		{
			Tags {"Name" = "Blur", "Type" = "Compute"}

			HLSLPROGRAM
			#pragma compute Main

			cbuffer PerDispatch
			{
				float4 Resolution;
			};
			RWTexture2D<float4> UAV_Output;

			#include "../Private/Common.hlsl"

			[numthreads(8, 8, 1)]
			void Main(uint3 id : SV_DispatchThreadID)
			{
				UAV_Output[id.xy] = float4(id.x & id.y, (id.x & 15) / 15, (id.y & 15) / 15, 0);
			}
			ENDHLSL
		}

		Kernel
		{
			Tags {"Name" = "RTAO", "Type" = "RayTracing"}

			HLSLPROGRAM
			#pragma miss Miss
			#pragma anyHit AnyHit
			#pragma closeHit ClosestHit
			#pragma rayGeneration RayGeneration

			struct AOAttributeData
			{
				float2 barycentrics;
			};

			struct AORayPayload
			{
				float HitDistance;
			};

			cbuffer PerMaterial
			{
				float _SpecularLevel;
				float4 _BaseColor;
			};
			RWTexture2D<float4> UAV_Output;

			#include "../Private/Common.hlsl"

			void RayGeneration()
			{
				uint2 dispatchIdx = DispatchRaysIndex().xy;
				UAV_Output[dispatchIdx] = float4(dispatchIdx.x & dispatchIdx.y, (dispatchIdx.x & 15) / 15, (dispatchIdx.y & 15) / 15, 0);
			}

			void Miss(inout AORayPayload rayPayload : SV_RayPayload)
			{
				rayPayload.HitDistance = -1;
			}

			void AnyHit(inout AORayPayload rayPayload : SV_RayPayload, AOAttributeData attributeData : SV_IntersectionAttributes)
			{
				IgnoreHit();
			}

			void ClosestHit(inout AORayPayload rayPayload : SV_RayPayload, AOAttributeData attributeData : SV_IntersectionAttributes)
			{
				rayPayload.HitDistance = RayTCurrent();
			}
			ENDHLSL
		}
	}
}