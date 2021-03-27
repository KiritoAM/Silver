
//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "gui/platforms/graphics/renderer/windows/renderer_d3d11.h"

#include "core/shared/math/vector.h"
#include "engine/shared/application/application.h"
#include "engine/shared/game_framework/game_instance.h"
#include "engine/shared/game_framework/mesh.h"
#include "engine/shared/game_framework/world.h"
#include "gui/platforms/graphics/RHI/windows/d3d11/buffer_d3d11.h"
#include "gui/platforms/graphics/RHI/windows/d3d11/RHI_context_d3d11.h"
#include "gui/platforms/graphics/RHI/windows/d3d11/RHI_device_d3d11.h"
#include "gui/platforms/graphics/RHI/windows/d3d11/dxgi_info_manager.h"
#include "gui/platforms/graphics/RHI/windows/d3d11/pipeline_state_d3d11.h"
#include "gui/platforms/graphics/RHI/windows/d3d11/shader_d3d11.h"
#include "gui/platforms/graphics/RHI/windows/d3d11/RHI_swapchain_d3d11.h"
#include "gui/shared/screen.h"
#include "gui/shared/screen_manager.h"
#include "gui/shared/window/window.h"

#include <string>

namespace
{
	gui::DXGI_INFO_MANAGER s_dxgi_info_manager;
	const std::string s_shader_dir{ "C:/dev/Silver/data/shaders/" };
}

namespace gui
{
	RENDERER_D3D11::RENDERER_D3D11()
	{
		create_shaders();
	}

	RENDERER_D3D11::~RENDERER_D3D11() = default;

	void RENDERER_D3D11::setup_window( const uint32_t window_id )
	{
		const WINDOW* window = SCREEN_MANAGER::get_singleton()->get_screen( window_id )->get_window();
		const auto height = window->get_height();
		const auto width = window->get_width();
		HWND window_handle = static_cast<HWND>(window->get_native_window());

		m_window_contexts.try_emplace( window_id, WINDOW_CONTEXT_D3D11{ { width, height }, window_handle,
									   std::make_unique<SWAPCHAIN_D3D11>( window_handle, m_device, width, height,
									   RHI_Format_R8G8B8A8_Unorm, RHI_Present_Immediate | RHI_Swap_Flip_Discard, "swapchain_main" ) } );
	}

	void RENDERER_D3D11::create_shaders()
	{
		m_shaders[RendererShader::FIRST] = std::make_unique<SHADER_D3D11>();
		m_shaders[RendererShader::FIRST]->compile( m_device, RHI_Shader_Type::RHI_Shader_Vertex, core::RHI_Vertex_Type::RHI_Vertex_Type_Position, s_shader_dir + "first.hlsl" );
		
		m_shaders[RendererShader::FIRST_PIXEL] = std::make_unique<SHADER_D3D11>();
		m_shaders[RendererShader::FIRST_PIXEL]->compile( m_device, RHI_Shader_Type::RHI_Shader_Pixel, core::RHI_Vertex_Type::RHI_Vertex_Type_Position, s_shader_dir + "first.hlsl" );
	}

	void RENDERER_D3D11::create_shader( const RendererShader shader_id, const RHI_Shader_Type shader_type, const core::RHI_Vertex_Type vertex_type,
										const std::string& shader_name )
	{
		m_shaders[shader_id] = std::make_unique<SHADER_D3D11>();
		m_shaders[shader_id]->compile( m_device, shader_type, vertex_type, s_shader_dir + shader_name );
	}

	void RENDERER_D3D11::on_mesh_created( engine::MESH* mesh )
	{
		auto vertex_buffer = create_buffer<BUFFER_D3D11, core::RHI_Vertex_PosTexNorTan>( m_device, BUFFER_TYPE::VERTEX, mesh->get_vertices() );
		m_device.get_context()->set_vertex_buffer( *vertex_buffer, 0u );
	}

	void RENDERER_D3D11::pass_main()
	{
		pass_update_framebuffer();

		pass_gbuffer();
	}

	void RENDERER_D3D11::pass_update_framebuffer()
	{
		PIPELINE_STATE_D3D11 pipeline_state;

		if ( m_device.get_context()->begin_render_pass( pipeline_state ) )
		{
			update_framebuffer();
		}
	}

	bool RENDERER_D3D11::update_framebuffer()
	{


		return true;
	}

	void RENDERER_D3D11::pass_gbuffer()
	{
		auto vertex_shader = m_shaders[RendererShader::FIRST].get();
		auto pixel_shader = m_shaders[RendererShader::FIRST_PIXEL].get();

		PIPELINE_STATE_D3D11 pipeline_state;
		pipeline_state.m_vertex_shader = vertex_shader;
		pipeline_state.m_pixel_shader = pixel_shader;
		pipeline_state.primitive_topology = RHI_PrimitiveTopology_TriangleList;
		pipeline_state.m_viewport = { { 0.0f, 0.0f, 800.0f, 600.0f }, 0.2f, 0.3f };

		if ( m_device.get_context()->begin_render_pass( pipeline_state ) )
		{
			//m_device.get_swapchain()->clear_backbuffer( { 1.0f, 0.0f, 0.0f } );

			auto& game_instance = engine::APPLICATION::get_singleton()->get_main_game_instance();

			game_instance.set_world( new engine::WORLD );
			game_instance.get_world()->create_world_object( "mesh_filepath" );

			/*m_device.get_context()->m_device_context->OMSetRenderTargets( 1u, m_device.get_swapchain()->m_render_target_view.GetAddressOf(), nullptr );

			m_device.get_context()->draw( 3u, 0u );

			m_device.get_swapchain()->present();*/

			for ( const auto& [window_id, window_context] : m_window_contexts )
			{
				window_context.swapchain->clear_backbuffer( { 1.0f, 0.0f, 0.0f } );

				m_device.get_context()->m_device_context->OMSetRenderTargets( 1u, window_context.swapchain->m_render_target_view.GetAddressOf(), nullptr );

				s_dxgi_info_manager.Set();
				m_device.get_context()->draw( 3u, 0u );
				for ( const auto& message : s_dxgi_info_manager.GetMessages() )
				{
					ASSERT_FAILED( message );
				}

				window_context.swapchain->present();
			}
		}
	}
}
