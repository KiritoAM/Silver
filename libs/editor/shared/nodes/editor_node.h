
#pragma once

//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "engine/shared/game_framework/nodes/node.h"

#include <memory>
#include <vector>

namespace editor
{
	class EDITOR_BASE;

	class EDITOR_NODE : public engine::NODE
	{
	public:
		EDITOR_NODE();
		~EDITOR_NODE();

		bool receive_notification( engine::NODE_NOTIFICATION notification ) override;

	private:
		std::vector< std::unique_ptr<EDITOR_BASE> > m_active_editors;
	};
}
