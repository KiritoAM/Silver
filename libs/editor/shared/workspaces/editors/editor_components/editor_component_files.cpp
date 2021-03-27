
//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "editor/shared/workspaces/editors/editor_components/editor_component_files.h"

#include "editor/shared/ui/widgets/widget_assets.h"

namespace editor
{
	void EDITOR_COMPONENT_FILES::listen()
	{

	}

	void EDITOR_COMPONENT_FILES::setup_widgets()
	{
		m_children.emplace_back( new WIDGET_ASSETS );
	}
}
