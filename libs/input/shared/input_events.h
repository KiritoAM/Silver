//////////////////////////////////////////////////////////////////////
//! Copyright Alastair Melville
//////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "engine/shared/events/event_base.h"

#include "core/shared/patterns/unique_id.h"
#include "input/shared/input_forward_declares.h"

namespace input
{
	inline constexpr core::UNIQUE_ID MOUSE_MOVE_EVENT_ID{ 'MoMo' };

	struct MOUSE_MOVE_EVENT : public engine::EVENT
	{
		MOUSE_MOVE_EVENT( const MOUSE_POS_TYPE& in_position )
			: engine::EVENT{ MOUSE_MOVE_EVENT_ID }
			, current_position{ in_position }
		{}

		MOUSE_POS_TYPE current_position;
	};
}
