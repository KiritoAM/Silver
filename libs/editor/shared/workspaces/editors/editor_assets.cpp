
//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "editor/shared/workspaces/editors/editor_assets.h"

#include "editor/shared/workspaces/editors/editor_components/editor_component_files.h"

namespace editor
{
	EDITOR_ASSETS::EDITOR_ASSETS()
	{
		m_children.emplace_back( std::make_unique<EDITOR_COMPONENT_FILES>() );
	}

	EDITOR_ASSETS::~EDITOR_ASSETS() = default;

	bool EDITOR_ASSETS::receive_notification( const engine::NODE_NOTIFICATION notification )
	{
		auto handled = EDITOR_BASE::receive_notification( notification );

		switch ( notification )
		{
		case engine::NODE_NOTIFICATION::TICK:
			{

			}
			break;
		}

		return handled;
	}

	void EDITOR_ASSETS::listen()
	{

	}

	void EDITOR_ASSETS::setup_operations()
	{

	}

	void EDITOR_ASSETS::setup_widgets()
	{

	}

	void EDITOR_ASSETS::setup_keymap()
	{

	}
}
