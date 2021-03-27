
#pragma once

//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "gui/shared/graphics/RHI/pipeline_state_base.h"

namespace gui
{
	class SHADER_D3D11;
	class SWAPCHAIN_D3D11;

	struct PIPELINE_STATE_D3D11 : public PIPELINE_STATE_BASE
	{
		SHADER_D3D11* m_vertex_shader{ nullptr };
		SHADER_D3D11* m_pixel_shader{ nullptr };
		SHADER_D3D11* m_compute_shader{ nullptr };
		SWAPCHAIN_D3D11* m_swapchain{ nullptr };
	};
}
