
#include "common.hlsl"

float4 mainVS(Vertex_Pos input) : SV_POSITION
{
    return float4(input.position.xy, 0.0f, 1.0f);
}

float4 mainPS() : SV_TARGET
{
	return float4(1.0f, 1.0f, 0.0f, 1.0f);
}