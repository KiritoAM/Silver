
#include "engine/platforms/application/windows/application_windows.h"

#include <windows.h>

namespace
{
	LRESULT CALLBACK handle_windows_message( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
	{


		return ::DefWindowProcW( window, message, wparam, lparam );
	}
}

namespace engine
{
	APPLICATION_WINDOWS::APPLICATION_WINDOWS()
	{
		HINSTANCE instance = (HINSTANCE)GetModuleHandle( nullptr );

		// Register the Window Class
		WNDCLASSEX wc;
		wc.cbSize = sizeof( WNDCLASSEX );
		wc.style = 0;
		wc.lpfnWndProc = handle_windows_message;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = instance;
		wc.hIcon = LoadIcon( instance, IDI_APPLICATION );
		wc.hCursor = LoadCursor( instance, IDC_ARROW );
		wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wc.lpszMenuName = nullptr;
		wc.lpszClassName = L"my_application";;
		wc.hIconSm = LoadIcon( instance, IDI_APPLICATION );

		if ( !RegisterClassEx( &wc ) )
		{
			MessageBox( nullptr, L"Window registration failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK );
			return;
		}
	}

	void APPLICATION_WINDOWS::process_os_messages()
	{
		MSG message;
		while ( PeekMessageW( &message, nullptr, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage( &message );
			DispatchMessage( &message );
		}
	}
}