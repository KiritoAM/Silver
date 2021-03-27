
#pragma once

//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "core/shared/patterns/non_automatic_singleton.h"

#include "gui/shared/graphics/RHI/RHI_types.h"

#include <memory>
#include <string>

//////////////////////////////////////////////////////////////////////
//! Forward Declerations
//////////////////////////////////////////////////////////////////////

namespace core
{
	enum class RHI_Vertex_Type : uint8_t;
}

namespace gui
{
	class RENDERER_BASE;
	enum class RendererShader : uint8_t;
	enum class RHI_Shader_Type : uint8_t;

	class RENDERER : public core::NON_AUTOMATIC_SINGLETON<RENDERER>
	{
	public:
		void tick( float delta_time );

		void setup_window( uint32_t window_id );

		void create_shader( RendererShader shader_id, RHI_Shader_Type shader_type, core::RHI_Vertex_Type vertex_type, const std::string& shader_name );

		// Render Passes
		void pass_main();
		void pass_update_framebuffer();
		
	//private:
		friend class core::NON_AUTOMATIC_SINGLETON<RENDERER>;
		RENDERER( RHI_Api_Type api_type );
		~RENDERER();

		std::unique_ptr<RENDERER_BASE> m_impl;
		RHI_Api_Type m_api_type{};
	};
}
