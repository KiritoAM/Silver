

//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "application/game_application.h"

#include "core/shared/build_config.h"
#include "engine/shared/events/events_manager.h"
#include "engine/shared/game_framework/nodes/engine_node.h"

#if INPUT_AVAILABLE
#include "input/shared/input_manager/input_manager.h"
#endif

#if GUI_AVAILABLE
#include "gui/shared/graphics/renderer/renderer.h"
#include "gui/shared/graphics/RHI/RHI_device.h"
#include "gui/shared/graphics/RHI/RHI_types.h"
#include "gui/shared/nodes/gui_node.h"
#include "gui/shared/screen/screen_manager.h"
#endif

#if EDITOR
#include "editor/shared/nodes/editor_node.h"
#endif

namespace engine
{
	APPLICATION* APPLICATION::create_singleton_custom()
	{
		return new app::GAME_APPLICATION;
	}
}

namespace app
{
	void GAME_APPLICATION::initialise_libraries()
	{
		engine::EVENTS_MANAGER::create_singleton();

		if constexpr ( core::input_available() )
		{
			input::INPUT_MANAGER::create_singleton();
		}

		// Add some library-specific functionality to the application through their corresponding nodes.
		// The order in which the nodes are added is important - it determines in which order the node tree processes them.
		auto& game_instance = get_main_game_instance();

		game_instance.add_node_to_root( new engine::ENGINE_NODE );

		if constexpr ( core::gui_available() )
		{
			auto renderer = gui::RENDERER::create_singleton( gui::RHI_Api_Type::RHI_Api_D3d11 );

			auto screen_manager = gui::SCREEN_MANAGER::create_singleton();
			screen_manager->create_window();
			//screen_manager->create_window();

			game_instance.add_node_to_root( new gui::GUI_NODE );
		}

		if constexpr ( core::is_editor() )
		{
			game_instance.add_node_to_root( new editor::EDITOR_NODE );
		}

		gui::RENDERER::get_singleton()->pass_main();
	}
}
