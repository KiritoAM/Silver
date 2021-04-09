
#include "common.hlsl"

float4 mainVS(float2 pos : POSITION) : SV_POSITION
{
    return float4(pos.x, pos.y, 0.0f, 1.0f);
}

float4 mainPS(Pixel_PosUv input) : SV_TARGET
{
    return tex.Sample(sampler_point_clamp, input.uv);
}
