
//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "gui/shared/graphics/renderer/renderer.h"

#include "gui/platforms/graphics/renderer/windows/renderer_d3d11.h"

namespace gui
{
	RENDERER::RENDERER( const RHI_Api_Type api_type )
		: m_api_type{ api_type }
	{
		switch ( m_api_type )
		{
		case RHI_Api_Type::RHI_Api_D3d11:
			{
				m_impl = std::make_unique<RENDERER_D3D11>();
				break;
			}
		case RHI_Api_Type::RHI_Api_Vulkan:
			{

				break;
			}
		}
	}

	RENDERER::~RENDERER() = default;

	void RENDERER::tick( float delta_time )
	{
		pass_main();
	}

	void RENDERER::setup_window( const uint32_t window_id )
	{
		switch ( m_api_type )
		{
		case RHI_Api_Type::RHI_Api_D3d11:
			{
				static_cast<RENDERER_D3D11*>(m_impl.get())->setup_window( window_id );
				break;
			}
		}
	}

	void RENDERER::create_shader( const RendererShader shader_id, const RHI_Shader_Type shader_type, 
								  const core::RHI_Vertex_Type vertex_type, const std::string& shader_name )
	{
		switch ( m_api_type )
		{
		case RHI_Api_Type::RHI_Api_D3d11:
			{
				static_cast<RENDERER_D3D11*>(m_impl.get())->create_shader( shader_id, shader_type, vertex_type, shader_name );
				break;
			}
		}
	}

	void RENDERER::pass_main()
	{
		switch ( m_api_type )
		{
		case RHI_Api_Type::RHI_Api_D3d11:
			{
				static_cast<RENDERER_D3D11*>(m_impl.get())->pass_main();
				break;
			}
		}
	}

	void RENDERER::pass_update_framebuffer()
	{
		switch ( m_api_type )
		{
		case RHI_Api_Type::RHI_Api_D3d11:
			{
				static_cast<RENDERER_D3D11*>(m_impl.get())->pass_update_framebuffer();
				break;
			}
		}
	}
}
