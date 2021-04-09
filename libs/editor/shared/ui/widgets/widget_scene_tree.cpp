
//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "editor/shared/ui/widgets/widget_scene_tree.h"

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
	WIDGET_SCENE_TREE::WIDGET_SCENE_TREE()
	{
		m_title = "SceneTree";
		m_flags |= ImGuiWindowFlags_HorizontalScrollbar;

		//m_position = { 800.0f, 0.0f };
		m_max_size = { 1000.0f, 800.0f };
		m_size = { 200.0f, 600.0f };
	}

	bool WIDGET_SCENE_TREE::receive_event( const engine::EVENT& in_event )
	{
		bool handled{ false };

		switch ( in_event.unique_id )
		{
		case engine::TICK_EVENT_ID:
			{
				handled = WIDGET::receive_event( in_event );
			}
			break;
		case input::MOUSE_MOVE_EVENT_ID:
			{
				handled = WIDGET::receive_event( in_event );

				auto mouse_move_event = static_cast<const input::MOUSE_MOVE_EVENT&>(in_event);

				if ( get_bounds().is_within( mouse_move_event.current_position ) )
				{
					receive_event( { gui::MARK_FOR_RENDER_EVENT_ID } );
				}
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

	void WIDGET_SCENE_TREE::add_children_to_tree( NODE* node )
	{
		const auto& child_nodes = node->get_children();
		for ( size_t index{ 0 }; index < child_nodes.size(); ++index )
		{
			switch ( child_nodes[index]->get_node_type() )
			{
			case engine::NODE_BRANCH_TYPE::NONE:
			case engine::NODE_BRANCH_TYPE::WORLD_ROOT:
				{
					add_node_to_tree( child_nodes[index].get() );
				}
				break;
			case engine::NODE_BRANCH_TYPE::ENGINE_ROOT:
			case engine::NODE_BRANCH_TYPE::GRAPHICS_ROOT:
			case engine::NODE_BRANCH_TYPE::EDITOR_ROOT:
				break;
			}
		}
	}

	void WIDGET_SCENE_TREE::add_node_to_tree( NODE* node )
	{
		if ( !node )
		{
			return;
		}

		ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_SpanFullWidth;
		node_flags |= node->has_children() ? ImGuiTreeNodeFlags_OpenOnArrow : ImGuiTreeNodeFlags_Leaf;

		if ( ImGui::TreeNodeEx( "gfd", node_flags ) )
		{
			add_children_to_tree( node );

			ImGui::TreePop();
		}
	}

	void WIDGET_SCENE_TREE::render()
	{
		if ( m_is_visible )
		{
			//core::SCOPED_VALUE scoped_value{ m_should_render, false };

			if ( ImGui::TreeNodeEx( "Root", ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_SpanFullWidth ) )
			{
				auto& game_instance = engine::APPLICATION::get_singleton()->get_main_game_instance();
				engine::NODE* root_node = game_instance.get_node_tree()->get_root_node();

				add_children_to_tree( root_node );

				ImGui::TreePop();
			}
		}
	}
}
