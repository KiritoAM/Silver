//////////////////////////////////////////////////////////////////////
//! Copyright Alastair Melville
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "gui/shared/screen_manager.h"

#include "gui/shared/screen.h"
#include "gui/shared/graphics/renderer/renderer.h"

namespace gui
{
	SCREEN_MANAGER::SCREEN_MANAGER() = default;
	
	SCREEN_MANAGER::~SCREEN_MANAGER() = default;

	uint32_t SCREEN_MANAGER::create_window()
	{
		static uint32_t window_id{ 0 };
		m_screens.try_emplace( window_id, std::make_unique<SCREEN>() );

		RENDERER::get_singleton()->setup_window( window_id );

		return window_id++;
	}

	void SCREEN_MANAGER::tick()
	{
		//m_screen->paint();
	}
}
