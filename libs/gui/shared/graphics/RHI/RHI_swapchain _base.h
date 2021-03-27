
#pragma once

//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "gui/shared/graphics/RHI/RHI_types.h"

namespace gui
{
	class SWAPCHAIN_BASE
	{
	public:
		static inline constexpr uint8_t s_swap_chain_buffer_count{ 3 };

	protected:
		bool m_windowed = false;
		uint32_t m_buffer_count = 0;
		uint32_t m_width = 0;
		uint32_t m_height = 0;
		uint32_t m_flags = 0;
		RHI_Format m_format = RHI_Format_R8G8B8A8_Unorm;
	};
}
