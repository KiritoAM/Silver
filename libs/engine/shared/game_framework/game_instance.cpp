
#include "engine/shared/game_framework/game_instance.h"

#include "engine/shared/game_framework/nodes/node_tree.h"
#include "engine/shared/game_framework/nodes/node.h"
#include "engine/shared/game_framework/world.h"

namespace engine
{
	GAME_INSTANCE::GAME_INSTANCE()
		: m_node_tree{ std::make_unique<NODE_TREE>() }
	{}

	GAME_INSTANCE::~GAME_INSTANCE() = default;

	void GAME_INSTANCE::tick()
	{
		m_node_tree->tick();
	}

	WORLD* GAME_INSTANCE::create_world()
	{
		m_world = std::make_unique<WORLD>();
		return m_world.get();
	}

	void GAME_INSTANCE::set_world( WORLD* world )
	{
		m_world = std::unique_ptr<WORLD>( world );
	}

	void GAME_INSTANCE::add_node( NODE* node )
	{
		m_node_tree->add_child( node );
	}
}
