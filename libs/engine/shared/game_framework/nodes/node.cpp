
//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "engine/shared/game_framework/nodes/node.h"

namespace engine
{
	bool NODE::receive_notification( const NODE_NOTIFICATION notification )
	{
		bool handled{ false };

		// Pass notification to children
		for ( auto& child : m_children )
		{
			child->receive_notification( notification );
		}

		switch ( notification )
		{
		case NODE_NOTIFICATION::TICK:
			{

			}
			break;
		case NODE_NOTIFICATION::ENTER_TREE:
			{

			}
			break;
		case NODE_NOTIFICATION::EXIT_TREE:
			{

			}
			break;
		case NODE_NOTIFICATION::PRE_DELETE:
			{
				m_children.clear();
			}
			break;
		}

		return handled;
	}

	void NODE::add_child( NODE* node )
	{
		m_children.emplace_back( std::make_unique<NODE>(node) );
	}
}
