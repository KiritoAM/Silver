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

namespace graphics
{
	class RENDERER;
}

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
		
		bool receive_notification( engine::NODE_NOTIFICATION notification ) override;

		//virtual core::RECTANGLE<int32_t> calculate_desired_size() = 0; // todo make protected

		//virtual void arrange() = 0;

		//virtual void paint(graphics::RENDERER& renderer) = 0;

		const core::RECTANGLE<int32_t>& get_bounds() const;

	protected:
		bool m_is_visible{};
		uint8_t m_var_pushes{};
		int32_t m_flags{};
		std::optional<float> m_alpha;
		core::FVECTOR2D m_position;
		core::FVECTOR2D m_padding;
		core::FVECTOR2D m_size;
		core::FVECTOR2D m_max_size;
		ImGuiWindow* m_window{ nullptr };
		std::string m_title{ "Boo" };

	private:
		struct impl;
		std::unique_ptr<impl> m_impl;
	};
}
