
//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "editor/shared/nodes/editor_node.h"

#include "editor/shared/workspaces/editors/editor_base.h"
#include "editor/shared/workspaces/editors/editor_assets.h"

namespace editor
{
	EDITOR_NODE::EDITOR_NODE()
	{
		m_children.emplace_back( std::make_unique<EDITOR_ASSETS>() );
	}

	EDITOR_NODE::~EDITOR_NODE() = default;

	bool EDITOR_NODE::receive_notification( const engine::NODE_NOTIFICATION notification )
	{
		auto handled = NODE::receive_notification( notification );

		switch ( notification )
		{
		case engine::NODE_NOTIFICATION::TICK:
			{
				
			}
			break;
		}

		return handled;
	}
}
