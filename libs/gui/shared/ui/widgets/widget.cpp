//////////////////////////////////////////////////////////////////////
//! Copyright Alastair Melville
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "gui/shared/ui/widgets/widget.h"

#include "core/shared/math/rectangle.h"
#include "engine/shared/events/event_base.h"
#include "gui/shared/events/render_events.h"
#include "gui/shared/imgui/imgui.h"

#include <gui/thirdparty/imgui/imgui_internal.h>

namespace gui
{
	struct WIDGET::IMPL
	{
		core::RECTANGLE<int32_t> m_bounds{ 0, 0, 0, 0 };
	};
}

namespace gui
{
	WIDGET::WIDGET()
		: m_impl{ std::make_unique<IMPL>() }
	{
		m_should_render = m_is_visible = true; // temp
	}

	WIDGET::~WIDGET() = default;

	bool WIDGET::receive_event( const engine::EVENT& in_event )
	{
		auto handled = engine::NODE::receive_event( in_event );

		switch ( in_event.unique_id )
		{
		case gui::MARK_FOR_RENDER_EVENT_ID:
			{
				m_should_render = true;
			}
			break;
		case gui::RENDER_IMGUI_EVENT_ID:
			{
				if ( m_is_visible )
				{
					if ( m_position != core::FVECTOR2D::ZERO_VALUE )
					{
						ImGui::SetNextWindowPos( { m_position.x, m_position.y } );
					}

					if ( m_padding != core::FVECTOR2D::ZERO_VALUE )
					{
						ImGui::PushStyleVar( ImGuiStyleVar_WindowPadding, { m_padding.x, m_padding.y } );
						++m_var_pushes;
					}

					if ( m_alpha.has_value() )
					{
						ImGui::PushStyleVar( ImGuiStyleVar_Alpha, m_alpha.value() );
						++m_var_pushes;
					}

					if ( m_size != core::FVECTOR2D::ZERO_VALUE )
					{
						ImGui::SetNextWindowSize( { m_size.x, m_size.y }, ImGuiCond_FirstUseEver );
					}

					if ( m_size != core::FVECTOR2D::ZERO_VALUE || m_max_size != core::FVECTOR2D::ZERO_VALUE )
					{
						ImGui::SetNextWindowSizeConstraints( { m_size.x, m_size.y }, { m_max_size.x, m_max_size.y } );
					}

					bool begun{ false };

					if ( ImGui::Begin( m_title.c_str(), &m_is_visible, m_flags ) )
					{
						m_window = ImGui::GetCurrentWindow();
						begun = true;
					}
					else if ( m_window && m_window->Hidden )
					{
						// Enters here if the window is hidden as part of an unselected tab.
						// ImGui::Begin() makes the window but returns false, then ImGui still expects ImGui::End() to be called.
						// So we make sure that when Widget::End() is called, ImGui::End() get's called as well.
						// Note: ImGui's docking is in beta, so maybe it's at fault here ?
						begun = true;
					}

					if ( m_window && m_window->Appearing )
					{
						//OnShow();
					}
					else if ( !m_is_visible )
					{
						//OnHide();
					}

					if ( begun )
					{
						render();

						ImGui::End();

						ImGui::PopStyleVar( m_var_pushes );
						m_var_pushes = 0;
					}
				}
			}
			break;
		}

		return handled;
	}

	const core::RECTANGLE<int32_t>& WIDGET::get_bounds() const
	{
		return m_impl->m_bounds;
	}
}
