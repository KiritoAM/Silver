
//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "editor/shared/ui/widgets/widget_assets.h"

namespace editor
{
	bool WIDGET_ASSETS::receive_notification( const engine::NODE_NOTIFICATION notification )
	{
		auto handled = WIDGET::receive_notification( notification );

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
