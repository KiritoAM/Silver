
#pragma once

//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "core/shared/type_wrappers/vector.h"

#include <memory>

namespace engine
{
	enum NODE_NOTIFICATION : uint8_t
	{
		TICK,
		ENTER_TREE,
		EXIT_TREE,
		PRE_DELETE,
	};
}

namespace engine
{
	class NODE
	{
	public:
		NODE() = default;

		virtual bool receive_notification( NODE_NOTIFICATION notification );

		void add_child( NODE* node );

	protected:
		core::VECTOR< std::unique_ptr<NODE> > m_children;

	private:
		~NODE() = default;
	};
}
