//////////////////////////////////////////////////////////////////////
//! Copyright Alastair Melville
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "gui/shared/ui/widgets/widget.h"

#include "core/shared/math/rectangle.h"
#include "gui/shared/imgui/imgui.h"

#include <gui/thirdparty/imgui/imgui_internal.h>

namespace gui
{
	struct WIDGET::impl
	{
		core::RECTANGLE<int32_t> m_bounds{ 0, 0, 0, 0 };
	};
}

namespace gui
{
	WIDGET::WIDGET()
		: m_impl( std::make_unique<impl>() )
	{}

	WIDGET::~WIDGET() = default;

	bool WIDGET::receive_notification( const engine::NODE_NOTIFICATION notification )
	{
		auto handled = engine::NODE::receive_notification( notification );

		switch ( notification )
		{
		case engine::NODE_NOTIFICATION::TICK:
			{
				if ( m_is_visible )
				{
					bool begun{ false };

					if ( m_position != core::FVECTOR2D::ZERO_VALUE )
					{
						ImGui::SetNextWindowPos( { m_position.X, m_position.Y } );
					}

					if ( m_padding != core::FVECTOR2D::ZERO_VALUE )
					{
						ImGui::PushStyleVar( ImGuiStyleVar_WindowPadding, { m_padding.X, m_padding.Y } );
						++m_var_pushes;
					}

					if ( m_alpha.has_value() )
					{
						ImGui::PushStyleVar( ImGuiStyleVar_Alpha, m_alpha.value() );
						++m_var_pushes;
					}

					if ( m_size != core::FVECTOR2D::ZERO_VALUE )
					{
						ImGui::SetNextWindowSize( { m_size.X, m_size.Y }, ImGuiCond_FirstUseEver );
					}

					if ( m_size != core::FVECTOR2D::ZERO_VALUE || m_max_size != core::FVECTOR2D::ZERO_VALUE )
					{
						ImGui::SetNextWindowSizeConstraints( { m_size.X, m_size.Y }, { m_max_size.X, m_max_size.Y } );
					}

					// Begin
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
