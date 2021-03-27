//////////////////////////////////////////////////////////////////////
//! Copyright Alastair Melville
//////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include <memory>

namespace engine
{
	class NODE;
	class NODE_TREE;
	class WORLD;

	class GAME_INSTANCE
	{
	public:
		GAME_INSTANCE();
		~GAME_INSTANCE();

		void tick();

		WORLD* create_world(); //! @todo remove?

		void set_world( WORLD* world );

		WORLD* get_world() const { return m_world.get(); }

		void add_node( NODE* node );

	protected:
		std::unique_ptr<WORLD> m_world;
		std::unique_ptr<NODE_TREE> m_node_tree;
	};
}