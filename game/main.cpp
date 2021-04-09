
//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "engine/shared/application/application.h"

#include <windows.h>

int WINAPI wWinMain( _In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPWSTR, _In_ int )
{
	auto application = engine::APPLICATION::create_singleton();
	application->run_loop();

	return 0;
}
