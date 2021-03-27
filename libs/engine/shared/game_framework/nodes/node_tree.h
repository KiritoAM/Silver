
#pragma once

//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include <memory>

namespace engine
{
	class NODE;

	class NODE_TREE
	{
	public:
		NODE_TREE();
		~NODE_TREE();

		void tick();

		void add_node( NODE* node );

	private:
		std::unique_ptr<NODE> m_root_node;
	};
}
