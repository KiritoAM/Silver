//////////////////////////////////////////////////////////////////////
//! Copyright Alastair Melville
//////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "core/shared/math/vector2d.h"
#include "core/shared/patterns/delegate.h"
#include "input/shared/input_forward_declares.h"

namespace input
{
	enum class BUTTON : uint8_t;
}

namespace input
{
	class MOUSE_BASE
	{
	public:
		const MOUSE_POS_TYPE& get_previous_position() const { return m_previous_position; }
		const MOUSE_POS_TYPE& get_current_position() const { return m_current_position; }
		const MOUSE_POS_TYPE& get_pos_delta() const { return m_pos_delta; }
		const core::FVECTOR2D& get_pos_delta_norm() const { return m_pos_delta_norm; }
		bool is_left_button_down() const { return m_left_mouse_down; }
		bool is_right_button_down() const { return m_right_mouse_down; }
		bool is_middle_button_down() const { return m_middle_mouse_down; }

		core::MULTICAST_DELEGATE_TWO_PARAMS<void, BUTTON, bool> m_button_up_down;

	protected:
		virtual void on_mouse_moved();

		virtual void on_mouse_button_down(BUTTON in_pressed_button);
		virtual void on_mouse_button_up(BUTTON in_released_button);

		uint8_t m_left_mouse_down : 1;
		uint8_t m_right_mouse_down : 1;
		uint8_t m_middle_mouse_down : 1;

		MOUSE_POS_TYPE m_previous_position;
		MOUSE_POS_TYPE m_current_position;
		MOUSE_POS_TYPE m_pos_delta;
		core::FVECTOR2D m_pos_delta_norm;
	};
}
