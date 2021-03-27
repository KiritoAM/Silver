
#pragma once

//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "editor/shared/workspaces/editors/editor_base.h"

namespace editor
{
	class EDITOR_ASSETS : public EDITOR_BASE
	{
	public:
		EDITOR_ASSETS();
		~EDITOR_ASSETS();

		bool receive_notification( engine::NODE_NOTIFICATION notification ) override;

		void listen() override;

		void setup_operations() override;

		void setup_widgets() override;

		void setup_keymap() override;
	};
}