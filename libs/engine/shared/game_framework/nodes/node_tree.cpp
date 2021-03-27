
//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "engine/shared/game_framework/nodes/node_tree.h"

#include "engine/shared/game_framework/nodes/node.h"

namespace engine
{
	NODE_TREE::NODE_TREE()
		: m_root_node{ std::make_unique<NODE>() }
	{}

	NODE_TREE::~NODE_TREE() = default;

	void NODE_TREE::tick()
	{
		m_root_node->receive_notification( NODE_NOTIFICATION::TICK );
	}

	void NODE_TREE::add_node( NODE* node )
	{
		m_root_node->add_child( node );
	}
}
