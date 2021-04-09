
cbuffer BufferFrame : register(b0)
{
	matrix g_view;
    matrix g_projection;
	
	matrix g_projection_orthographic;
    matrix g_view_projection_orthographic;
	
	matrix g_view_projection;
}

cbuffer BufferUber : register(b2)
{
    matrix g_transform;
	float2 g_resolution;
	float2 padding;
}
