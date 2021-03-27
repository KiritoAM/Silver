
#pragma once

//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "gui/shared/ui/widgets/widget.h"

namespace editor
{
	class WIDGET_ASSETS : public gui::WIDGET
	{
	public:
		bool receive_notification( engine::NODE_NOTIFICATION notification ) override;
	};
}
