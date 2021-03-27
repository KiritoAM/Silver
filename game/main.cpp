
//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include <windows.h>

#include "core/shared/build_config.h"
#include "engine/shared/application/application.h"
#include "engine/shared/clipboard/clipboard.h"
#include "gui/shared/screen_manager.h"

#include "gui/shared/graphics/renderer/renderer.h"
#include "gui/shared/graphics/RHI/RHI_device.h"
#include "gui/shared/graphics/RHI/RHI_types.h"

#include <memory>

#if EDITOR
#include "editor/shared/nodes/editor_node.h"
#endif

int WINAPI wWinMain( _In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPWSTR, _In_ int )
{
	auto application = engine::APPLICATION::create_singleton();

	/*std::string text( "Hello! \r" );
	engine::CLIPBOARD::get_text( text, nullptr );
	engine::CLIPBOARD::set_text( text, nullptr );
	engine::CLIPBOARD::get_text( text, nullptr );*/

	auto renderer = gui::RENDERER::create_singleton( gui::RHI_Api_Type::RHI_Api_D3d11 );

	auto screen_manager = gui::SCREEN_MANAGER::create_singleton();
	screen_manager->create_window();
	screen_manager->create_window();

	renderer->pass_main();

	if constexpr ( core::is_editor() )
	{
		auto& game_instance = application->get_main_game_instance();
		game_instance.add_node( new editor::EDITOR_NODE );
	}

	application->run_loop();

	return 0;
}
