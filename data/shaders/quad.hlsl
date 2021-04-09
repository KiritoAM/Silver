
#include "common.hlsl"

Pixel_PosUv mainVS(Vertex_PosUv input)
{
    Pixel_PosUv output;
    
    input.position.w    = 1.0f;
    output.position     = mul(input.position, g_view_projection_orthographic);
    output.uv           = input.uv;
    
    return output;
}

float4 mainPS(Pixel_PosUv input) : SV_TARGET
{
    return tex.Sample(sampler_point_clamp, input.uv);
}
