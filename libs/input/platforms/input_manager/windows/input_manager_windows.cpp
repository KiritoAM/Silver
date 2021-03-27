//////////////////////////////////////////////////////////////////////
//! Copyright Alastair Melville
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "input/platforms/input_manager/windows/input_manager_windows.h"

#include "input/shared/keyboard/keyboard.h"
#include "input/shared/mouse/mouse.h"

namespace input
{
	bool INPUT_MANAGER_WINDOWS::handle_platform_message(HWND in_window, uint32_t in_message, WPARAM in_wparam, LPARAM in_lparam)
	{
		if (input::KEYBOARD::get_singleton().handle_message(in_window, in_message, in_wparam, in_lparam))
		{
			return true;
		}

		if (input::POINTING_DEVICE::get_singleton().handle_message(in_window, in_message, in_wparam, in_lparam))
		{
			return true;
		}

		return false;
	}
}
