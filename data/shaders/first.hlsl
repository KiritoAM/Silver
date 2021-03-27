

float4 mainVS(float2 pos : POSITION) : SV_POSITION
{
    return float4(pos.x, pos.y, 0.0f, 1.0f);
}

float4 mainPS() : SV_TARGET
{
	return float4(1.0f, 1.0f, 0.0f, 1.0f);
}