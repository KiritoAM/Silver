
#pragma once

namespace gui
{
	enum RHI_PhysicalDevice_Type
	{
		RHI_PhysicalDevice_Unknown,
		RHI_PhysicalDevice_Integrated,
		RHI_PhysicalDevice_Discrete,
		RHI_PhysicalDevice_Virtual,
		RHI_PhysicalDevice_Cpu
	};

	enum class RHI_Api_Type : uint8_t
	{
		RHI_Api_D3d11,
		RHI_Api_D3d12,
		RHI_Api_Vulkan
	};

	enum RHI_Present_Mode : uint32_t
	{
		RHI_Present_Immediate = 1 << 0, // Doesn't wait.                  Frames are not dropped. Tearing.
		RHI_Present_Mailbox = 1 << 1, // Waits for v-blank.             Frames are dropped.     No tearing.
		RHI_Present_Fifo = 1 << 2, // Waits for v-blank, every time. Frames are not dropped. No tearing.
		RHI_Present_FifoRelaxed = 1 << 3, // Waits for v-blank, once.       Frames are not dropped. Tearing.
		RHI_Present_SharedDemandRefresh = 1 << 4,
		RHI_Present_SharedDContinuousRefresh = 1 << 5,

		// D3D11 only flags as match to Vulkan is possible
		RHI_Swap_Discard = 1 << 6,
		RHI_Swap_Sequential = 1 << 7,
		RHI_Swap_Flip_Sequential = 1 << 8,
		RHI_Swap_Flip_Discard = 1 << 9,
		RHI_SwapChain_Allow_Mode_Switch = 1 << 10
	};

	enum RHI_Queue_Type
	{
		RHI_Queue_Graphics,
		RHI_Queue_Transfer,
		RHI_Queue_Compute,
		RHI_Queue_Undefined
	};

	enum RHI_Query_Type
	{
		RHI_Query_Timestamp,
		RHI_Query_Timestamp_Disjoint
	};

	enum RHI_PrimitiveTopology_Mode
	{
		RHI_PrimitiveTopology_TriangleList,
		RHI_PrimitiveTopology_LineList,
		RHI_PrimitiveTopology_Unknown
	};

	enum RHI_Cull_Mode
	{
		RHI_Cull_None,
		RHI_Cull_Front,
		RHI_Cull_Back,
		RHI_Cull_Undefined
	};

	enum RHI_Fill_Mode
	{
		RHI_Fill_Solid,
		RHI_Fill_Wireframe,
		RHI_Fill_Undefined
	};

	enum RHI_Filter
	{
		RHI_Filter_Nearest,
		RHI_Filter_Linear,
	};

	enum RHI_Sampler_Mipmap_Mode
	{
		RHI_Sampler_Mipmap_Nearest,
		RHI_Sampler_Mipmap_Linear,
	};

	enum RHI_Sampler_Address_Mode
	{
		RHI_Sampler_Address_Wrap,
		RHI_Sampler_Address_Mirror,
		RHI_Sampler_Address_Clamp,
		RHI_Sampler_Address_Border,
		RHI_Sampler_Address_MirrorOnce,
	};

	enum RHI_Comparison_Function
	{
		RHI_Comparison_Never,
		RHI_Comparison_Less,
		RHI_Comparison_Equal,
		RHI_Comparison_LessEqual,
		RHI_Comparison_Greater,
		RHI_Comparison_NotEqual,
		RHI_Comparison_GreaterEqual,
		RHI_Comparison_Always
	};

	enum RHI_Stencil_Operation
	{
		RHI_Stencil_Keep,
		RHI_Stencil_Zero,
		RHI_Stencil_Replace,
		RHI_Stencil_Incr_Sat,
		RHI_Stencil_Decr_Sat,
		RHI_Stencil_Invert,
		RHI_Stencil_Incr,
		RHI_Stencil_Decr
	};

	enum RHI_Format : uint32_t // gets serialized so better be explicit
	{
		// R
		RHI_Format_R8_Unorm,
		RHI_Format_R16_Uint,
		RHI_Format_R16_Float,
		RHI_Format_R32_Uint,
		RHI_Format_R32_Float,
		// RG
		RHI_Format_R8G8_Unorm,
		RHI_Format_R16G16_Float,
		RHI_Format_R32G32_Float,
		// RGB
		RHI_Format_R11G11B10_Float,
		RHI_Format_R32G32B32_Float,
		// RGBA
		RHI_Format_R8G8B8A8_Unorm,
		RHI_Format_R10G10B10A2_Unorm,
		RHI_Format_R16G16B16A16_Snorm,
		RHI_Format_R16G16B16A16_Float,
		RHI_Format_R32G32B32A32_Float,
		// DEPTH
		RHI_Format_D32_Float,
		RHI_Format_D32_Float_S8X24_Uint,

		RHI_Format_Undefined
	};

	enum RHI_Blend
	{
		RHI_Blend_Zero,
		RHI_Blend_One,
		RHI_Blend_Src_Color,
		RHI_Blend_Inv_Src_Color,
		RHI_Blend_Src_Alpha,
		RHI_Blend_Inv_Src_Alpha,
		RHI_Blend_Dest_Alpha,
		RHI_Blend_Inv_Dest_Alpha,
		RHI_Blend_Dest_Color,
		RHI_Blend_Inv_Dest_Color,
		RHI_Blend_Src_Alpha_Sat,
		RHI_Blend_Blend_Factor,
		RHI_Blend_Inv_Blend_Factor,
		RHI_Blend_Src1_Color,
		RHI_Blend_Inv_Src1_Color,
		RHI_Blend_Src1_Alpha,
		RHI_Blend_Inv_Src1_Alpha
	};

	enum RHI_Blend_Operation
	{
		RHI_Blend_Operation_Add,
		RHI_Blend_Operation_Subtract,
		RHI_Blend_Operation_Rev_Subtract,
		RHI_Blend_Operation_Min,
		RHI_Blend_Operation_Max
	};

	enum class RHI_Descriptor_Type
	{
		Sampler,
		Texture,
		ConstantBuffer,
		Undefined
	};

	enum class RHI_Image_Layout
	{
		Undefined,
		General,
		Preinitialized,
		Color_Attachment_Optimal,
		Depth_Stencil_Attachment_Optimal,
		Depth_Stencil_Read_Only_Optimal,
		Shader_Read_Only_Optimal,
		Transfer_Dst_Optimal,
		Present_Src
	};

	enum class RHI_Semaphore_State
	{
		Idle,
		Submitted,
		Signaled
	};

	inline const char* rhi_format_to_string( const RHI_Format result )
	{
		switch ( result )
		{
		case RHI_Format_R8_Unorm:               return "RHI_Format_R8_Unorm";
		case RHI_Format_R16_Uint:               return "RHI_Format_R16_Uint";
		case RHI_Format_R16_Float:              return "RHI_Format_R16_Float";
		case RHI_Format_R32_Uint:               return "RHI_Format_R32_Uint";
		case RHI_Format_R32_Float:              return "RHI_Format_R32_Float";
		case RHI_Format_R8G8_Unorm:             return "RHI_Format_R8G8_Unorm";
		case RHI_Format_R16G16_Float:           return "RHI_Format_R16G16_Float";
		case RHI_Format_R32G32_Float:           return "RHI_Format_R32G32_Float";
		case RHI_Format_R32G32B32_Float:        return "RHI_Format_R32G32B32_Float";
		case RHI_Format_R8G8B8A8_Unorm:         return "RHI_Format_R8G8B8A8_Unorm";
		case RHI_Format_R16G16B16A16_Float:     return "RHI_Format_R16G16B16A16_Float";
		case RHI_Format_R32G32B32A32_Float:     return "RHI_Format_R32G32B32A32_Float";
		case RHI_Format_D32_Float:              return "RHI_Format_D32_Float";
		case RHI_Format_D32_Float_S8X24_Uint:   return "RHI_Format_D32_Float_S8X24_Uint";
		case RHI_Format_Undefined:              return "RHI_Format_Undefined";
		}

		return "Unknown format";
	}

	enum class RHI_Shader_Type : uint8_t
	{
		RHI_Shader_Unknown = 0,
		RHI_Shader_Vertex = 1 << 0,
		RHI_Shader_Pixel = 1 << 1,
		RHI_Shader_Compute = 1 << 2,
	};

	enum class BUFFER_TYPE : uint8_t
	{
		UNKNOWN = 0,
		VERTEX = 1 << 0,
		INDEX = 1 << 1,
		CONSTANT = 1 << 2,
	};

	enum class Shader_Compilation_State
	{
		Idle,
		Compiling,
		Succeeded,
		Failed
	};
}