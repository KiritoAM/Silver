//////////////////////////////////////////////////////////////////////
//! Copyright Alastair Melville
//////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "engine/shared/game_framework/nodes/node.h"

#include "core/shared/math/vector2d.h"

#include <memory>
#include <optional>
#include <string>

//////////////////////////////////////////////////////////////////////
//! Forward Declerations
//////////////////////////////////////////////////////////////////////

struct ImGuiWindow;

namespace core
{
	template<typename TYPE>
	struct RECTANGLE;
}

namespace gui
{
	class WIDGET : public engine::NODE
	{
	public:
		WIDGET();
		virtual ~WIDGET();
		
		bool receive_event( const engine::EVENT& in_event ) override;

		//virtual core::RECTANGLE<int32_t> calculate_desired_size() = 0; // todo make protected

		//virtual void arrange() = 0;

		//virtual void paint(graphics::RENDERER& renderer) = 0;

		const core::RECTANGLE<int32_t>& get_bounds() const;

		bool set_size( const core::FVECTOR2D& possible_new_size )
		{
			if ( possible_new_size <= m_max_size )
			{
				m_size = possible_new_size;
				return true;
			}
			else
			{
				return false;
			}
		}

	protected:
		virtual void render() = 0;

		bool m_is_visible{};
		bool m_should_render{};
		uint8_t m_var_pushes{};
		int32_t m_flags{};
		std::optional<float> m_alpha;
		core::FVECTOR2D m_position;
		core::FVECTOR2D m_padding;
		core::FVECTOR2D m_size;
		core::FVECTOR2D m_max_size;
		ImGuiWindow* m_window{ nullptr };
		std::string m_title{ "Unnamed" };

	private:
		struct IMPL;
		std::unique_ptr<IMPL> m_impl;
	};
}
