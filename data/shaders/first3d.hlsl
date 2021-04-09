
#include "common.hlsl"

float4 mainVS(Vertex_PosUvNorTan input) : SV_POSITION
{
	float4 out_position;

    input.position.w         = 1.0f;
    out_position             = mul(input.position, g_transform);
    out_position             = mul(out_position, g_view_projection);
	
	return out_position;
}

float4 mainPS() : SV_TARGET
{
	return float4(0.0f, 0.0f, 1.0f, 1.0f);
}