
#pragma once

//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "gui/shared/ui/widgets/widget.h"

#include <memory>

//////////////////////////////////////////////////////////////////////
//! Forward Declarations
//////////////////////////////////////////////////////////////////////

namespace engine
{
	class WORLD;
}

namespace gui
{
	class CAMERA3D;
}

namespace editor
{
	class WIDGET_VIEWPORT : public gui::WIDGET
	{
	public:
		WIDGET_VIEWPORT();
		~WIDGET_VIEWPORT() = default;

		bool receive_event( const engine::EVENT& in_event ) override;

	private:
		void render() override;

		std::unique_ptr<gui::CAMERA3D> m_camera3d;
		engine::WORLD* m_world{};
	};
}
