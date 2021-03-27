//////////////////////////////////////////////////////////////////////
//! Copyright Alastair Melville
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "input/platforms/mouse/windows/mouse_windows.h"

//#include "core/shared/patterns/delegate.h"
#include "input/shared/mouse/mouse_codes.h"

#include <WindowsX.h>

#include <iostream>
#include <sstream>

namespace input
{
	struct POINTING_DEVICE_WINDOWS::impl
	{
		HWND m_window;
		LPARAM m_lparam;
	};
}

namespace input
{
	POINTING_DEVICE_WINDOWS::POINTING_DEVICE_WINDOWS()
		: m_impl( std::make_unique<impl>() )
	{}

	POINTING_DEVICE_WINDOWS::~POINTING_DEVICE_WINDOWS() = default;

	bool POINTING_DEVICE_WINDOWS::handle_message(HWND in_window, uint32_t in_message, WPARAM in_wparam, LPARAM in_lparam)
	{
		m_impl->m_window = in_window;
		m_impl->m_lparam = in_lparam;

		switch (in_message)
		{
		case WM_LBUTTONDOWN:
		{
			on_mouse_button_down(BUTTON::LEFT);
			return true;
		}
		case WM_LBUTTONUP:
		{
			on_mouse_button_up(BUTTON::LEFT);
			return true;
		}
		case WM_MOUSEMOVE:
		{
			handle_absolute_input();
			on_mouse_moved();
			return true;
		}
		case WM_INPUT:
		{			
			if (handle_raw_input())
			{
				on_mouse_moved();
			}
			return true;
		}
		default:
		{
			return false;
		}
		}

		return true;
	}

	void POINTING_DEVICE_WINDOWS::handle_absolute_input()
	{
		m_previous_position = m_current_position;

		const MOUSE_POS_TYPE new_mouse_position(static_cast<MOUSE_AXIS_TYPE>(GET_X_LPARAM(m_impl->m_lparam)),
			static_cast<MOUSE_AXIS_TYPE>(GET_Y_LPARAM(m_impl->m_lparam)));

		m_current_position = new_mouse_position;
	}

	bool POINTING_DEVICE_WINDOWS::handle_raw_input()
	{
		UINT size;
		// get the size of the input data
		if (GetRawInputData(reinterpret_cast<HRAWINPUT>(m_impl->m_lparam), RID_INPUT, nullptr, &size, sizeof(RAWINPUTHEADER)) == -1)
		{
			return false;
		}

		std::vector<char> raw_buffer;
		raw_buffer.resize(size);

		// then read in the input data
		if (GetRawInputData(reinterpret_cast<HRAWINPUT>(m_impl->m_lparam), RID_INPUT, raw_buffer.data(), &size, sizeof(RAWINPUTHEADER)) != size)
		{
			return false;
		}

		// process the raw input data
		const RAWINPUT& raw_input = reinterpret_cast<const RAWINPUT&>(*raw_buffer.data());
		if (raw_input.header.dwType == RIM_TYPEMOUSE // only listen to mouse type messages
			&& (raw_input.data.mouse.lLastX != 0 || raw_input.data.mouse.lLastY != 0))
		{
			m_pos_delta = MOUSE_POS_TYPE(raw_input.data.mouse.lLastX, raw_input.data.mouse.lLastY);
			std::wostringstream os_;
			os_ << m_pos_delta.X << "\n";
			OutputDebugStringW(os_.str().c_str());
			//OutputDebugString("Stuff: " << m_pos_delta.X);
			return true;
		}

		return false;
	}

	void POINTING_DEVICE_WINDOWS::on_mouse_moved()
	{
		super::on_mouse_moved();
	}

	void POINTING_DEVICE_WINDOWS::on_mouse_button_down(const BUTTON in_pressed_button)
	{
		super::on_mouse_button_down(in_pressed_button);

		while (::ShowCursor(FALSE) >= 0);
	}

	void POINTING_DEVICE_WINDOWS::on_mouse_button_up(const BUTTON in_released_button)
	{
		super::on_mouse_button_up(in_released_button);

		while (::ShowCursor(TRUE) < 0);
	}
}
