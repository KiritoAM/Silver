
#include "common.hlsl"

Pixel_PosUv mainVS(Vertex_PosUvNorTan input)
{
	Pixel_PosUv output;

    input.position.w = 1.0f;
    output.position = mul(input.position, g_transform);
    output.position = mul(output.position, g_view_projection);
	output.uv = input.uv;
	
	return output;
}

float4 mainPS(Pixel_PosUv input) : SV_TARGET
{
    return material_albedo.Sample(sampler_point_clamp, input.uv);
}