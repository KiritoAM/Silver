//////////////////////////////////////////////////////////////////////
//! Copyright Alastair Melville
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "gui/shared/window/window_base.h"

namespace gui
{
	void WINDOW_BASE::set_bounds(const core::RECTANGLE<int32_t>& in_bounds)
	{
		m_bounds = in_bounds;
	}

	const core::RECTANGLE<int32_t>& WINDOW_BASE::get_bounds() const
	{
		return m_bounds;
	}

	uint32_t WINDOW_BASE::get_width() const
	{
		return static_cast<uint32_t>(m_bounds.get_width());
	}

	uint32_t WINDOW_BASE::get_height() const
	{
		return static_cast<uint32_t>(m_bounds.get_height());
	}
}
