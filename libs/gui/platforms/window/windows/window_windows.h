//////////////////////////////////////////////////////////////////////
//! Copyright Alastair Melville
//////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "gui/shared/window/window_base.h"

#include <string>
#include <Windows.h>

namespace gui
{
	class WINDOW_WINDOWS : public WINDOW_BASE
	{
	public:
		WINDOW_WINDOWS();

		HWND find_os_window(const std::string& in_window_name);

		HWND get_native_window() const { return m_window; }
		
	protected:
		void show_window();

	private:
		HWND m_window{ nullptr };
	};
}
