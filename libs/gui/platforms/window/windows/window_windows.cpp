//////////////////////////////////////////////////////////////////////
//! Copyright Alastair Melville
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "gui/platforms/window/windows/window_windows.h"

#include "core/shared/math/rectangle.h"

//#include <WtsApi32.h>

namespace gui
{
	WINDOW_WINDOWS::WINDOW_WINDOWS()
	{
		const core::RECTANGLE<int32_t>& window_bounds = get_bounds();
		if ( true )
		{
			RECT rect;
			::SetRect( &rect, window_bounds.get_left(), window_bounds.get_top(), window_bounds.get_width(), window_bounds.get_height() );
			::AdjustWindowRect( &rect, 13565952, false );
		}

		m_window = ::CreateWindowW( L"my_application", L"aaa", 13565952, window_bounds.get_left(), window_bounds.get_top(),
									window_bounds.get_width(), window_bounds.get_height(), nullptr, nullptr, (HINSTANCE)GetModuleHandle( nullptr ), nullptr );
		if ( m_window )
		{
			::SetWindowLongPtr( m_window, 0, (LONG_PTR)this );
			::GdiSetBatchLimit( 1 );
			//::WTSRegisterSessionNotification(m_window, NOTIFY_FOR_THIS_SESSION);
		}

		const HBRUSH__* brush = CreateSolidBrush( RGB( 0, 0, 0 ) );
		SetClassLongPtr( m_window, GCLP_HBRBACKGROUND, (LONG_PTR)brush );

		show_window();
	}

	HWND WINDOW_WINDOWS::find_os_window(const std::string& in_window_name)
	{
		HWND found_window = ::FindWindowEx( 0, 0, 0, LPCWSTR( in_window_name.c_str() ) );
		return found_window;
	}

	void WINDOW_WINDOWS::show_window()
	{
		// Get Windows to completely repaint desktop
		::InvalidateRect(nullptr, nullptr, true);

		::ShowWindow(m_window, SW_SHOWNORMAL);

		::SetForegroundWindow(m_window);
	}
}
