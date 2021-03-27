//////////////////////////////////////////////////////////////////////
//! Copyright Alastair Melville
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "input/shared/mouse/mouse_base.h"

#include "core/shared/math/rectangle.h"
//#include "graphics/shared/window/window.h"
#include "input/shared/mouse/mouse_codes.h"

namespace input
{
	void POINTING_DEVICE_BASE::on_mouse_moved()
	{
		// todo get the window that currently has focus, and maybe cache it
		/*gui::WINDOW* active_window = application::ENGINE::get_engine_window();
		const math::RECTANGLE<int32_t>& window_bounds = active_window->get_bounds();

		const float pos_delta_norm_x = static_cast<float>( m_pos_delta.X ) / static_cast<float>( window_bounds.get_width() );
		const float pos_delta_norm_y = static_cast<float>( m_pos_delta.Y ) / static_cast<float>( window_bounds.get_height() );
		m_pos_delta_norm = { pos_delta_norm_x, pos_delta_norm_y };*/
	}

	void POINTING_DEVICE_BASE::on_mouse_button_down(BUTTON in_pressed_button)
	{
		switch (in_pressed_button)
		{
		case BUTTON::LEFT:
		{
			m_left_mouse_down = true;
			break;
		}
		case BUTTON::RIGHT:
		{
			m_right_mouse_down = true;
			break;
		}
		case BUTTON::MIDDLE:
		{
			m_middle_mouse_down = true;
			break;
		}
		default:
		{
			return;
		}
		}

		m_button_up_down.m_inner.execute<void, BUTTON, bool>(std::move(in_pressed_button), true);
	}

	void POINTING_DEVICE_BASE::on_mouse_button_up(BUTTON in_released_button)
	{
		switch (in_released_button)
		{
		case BUTTON::LEFT:
		{
			m_left_mouse_down = false;
			break;
		}
		case BUTTON::RIGHT:
		{
			m_right_mouse_down = false;
			break;
		}
		case BUTTON::MIDDLE:
		{
			m_middle_mouse_down = false;
			break;
		}
		default:
		{
			return;
		}
		}

		m_button_up_down.m_inner.execute<void, BUTTON, bool>(std::move(in_released_button), false);
	}
}
