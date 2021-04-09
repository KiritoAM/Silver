
//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "editor/shared/ui/widgets/widget_viewport.h"

#include "core/shared/math/rectangle.h"
#include "core/shared/patterns/scoped_value.h"
#include "editor/shared/events/editor_events.h"
#include "engine/shared/application/application.h"
#include "engine/shared/game_framework/game_instance.h"
#include "engine/shared/game_framework/nodes/node_tree.h"
#include "gui/shared/events/render_events.h"
#include "gui/shared/imgui/imgui.h"
#include "input/shared/input_events.h"


namespace editor
{
	WIDGET_VIEWPORT::WIDGET_VIEWPORT()
	{
		static uint32_t unique_counter{ 0 };
		m_title = "Viewport" + std::to_string( unique_counter++ );
		m_flags |= ImGuiWindowFlags_NoScrollbar;

		//m_position = { 0.0f, 0.0f };
		m_max_size = { 1000.0f, 800.0f };
		m_size = { 800.0f, 600.0f };

		gui::RENDERER::get_singleton()->register_viewport( this, m_camera3d.get(), m_world );
	}

	bool WIDGET_VIEWPORT::receive_event( const engine::EVENT& in_event )
	{
		bool handled{ false };

		switch ( in_event.unique_id )
		{
		case engine::TICK_EVENT_ID:
			{
				handled = WIDGET::receive_event( in_event );
			}
			break;
		case gui::MARK_FOR_RENDER_EVENT_ID:
			{
				handled = WIDGET::receive_event( in_event );
			}
			break;
		case gui::RENDER_IMGUI_EVENT_ID:
			{
				if ( m_should_render )
				{
					handled = WIDGET::receive_event( in_event );
				}
			}
			break;
		}

		return handled;
	}

	void WIDGET_VIEWPORT::render()
	{
		if ( m_is_visible )
		{
			float width = static_cast<float>(ImGui::GetWindowContentRegionMax().x - ImGui::GetWindowContentRegionMin().x);
			float height = static_cast<float>(ImGui::GetWindowContentRegionMax().y - ImGui::GetWindowContentRegionMin().y);

			core::FVECTOR2D offset{ ImGui::GetWindowPos().x + m_padding.x, ImGui::GetWindowPos().y + m_padding.y };

			auto renderer = gui::RENDERER::get_singleton();

			if ( m_size.x != width || m_size.y != height)
			{
				//m_renderer->SetViewport( width, height, offset.x, offset.y );

				m_size = { width, height };
			}

			//auto viewport_texture = renderer->get_render_target( gui::RENDER_TARGET::REGION_TEST_0 )->get_resource_view();
			auto viewport_texture = gui::RENDERER::get_singleton()->get_viewport( this )->get_resource_view();

			ImGui::Image(
				static_cast<ImTextureID>(viewport_texture),
				{ width, height },
				ImVec2( 0, 0 ),
				ImVec2( 1, 1 ),
				ImColor( 255, 255, 255, 255 ),
				ImColor( 50, 127, 166, 255 )
			);
		}
	}
}
