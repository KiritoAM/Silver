
#pragma once

//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "editor/shared/workspaces/editors/editor_components/editor_component_base.h"

namespace editor
{
	class EDITOR_COMPONENT_FILES : public EDITOR_COMPONENT_BASE
	{
	public:
		void listen() override;

		void setup_widgets() override;
	};
}
