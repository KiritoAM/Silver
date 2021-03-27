//////////////////////////////////////////////////////////////////////
//! Copyright Alastair Melville
//////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "core/shared/math/rectangle.h"

namespace core
{
	template<typename TYPE>
	struct RECTANGLE;
}

namespace gui
{
	class WINDOW_BASE
	{
	public:
		void set_bounds(const core::RECTANGLE<int32_t>& in_bounds);
		const core::RECTANGLE<int32_t>& get_bounds() const;
		uint32_t get_width() const;
		uint32_t get_height() const;

		static inline uint8_t s_current_window_id{ 0 };
		uint8_t m_window_id{ 0 };

	protected:
		WINDOW_BASE() = default;
		virtual ~WINDOW_BASE() = default;

		core::RECTANGLE<int32_t> m_bounds{ 24, 1, 1063, 807 };
	};
}
