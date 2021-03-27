
#pragma once

//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "gui/shared/graphics/renderer/renderer_base.h"

#include "gui/platforms/graphics/RHI/windows/d3d11/command_list_d3d11.h"
#include "gui/platforms/graphics/RHI/windows/d3d11/RHI_device_d3d11.h"

#include <memory>
#include <unordered_map>

//////////////////////////////////////////////////////////////////////
//! Forward Declerations
//////////////////////////////////////////////////////////////////////

namespace core
{
	enum class RHI_Vertex_Type : uint8_t;
}

namespace gui
{
	class SHADER_D3D11;
	enum class RendererShader : uint8_t;
	enum class RHI_Shader_Type : uint8_t;

	struct WINDOW_CONTEXT_D3D11 : public WINDOW_CONTEXT
	{
		HWND window_handle;
		std::unique_ptr<SWAPCHAIN_D3D11> swapchain;
	};

	class RENDERER_D3D11 : public RENDERER_BASE
	{
	public:
		RENDERER_D3D11();
		~RENDERER_D3D11();

		void setup_window( uint32_t window_id );

		void create_shader( RendererShader shader_id, RHI_Shader_Type shader_type, core::RHI_Vertex_Type vertex_type, const std::string& shader_name );

		void pass_main();

		void pass_update_framebuffer();

		void pass_gbuffer();

	private:
		void on_mesh_created( engine::MESH* mesh ) override;

		void create_shaders();

		bool update_framebuffer();

		std::unordered_map<RendererShader, std::unique_ptr<SHADER_D3D11>> m_shaders;
		RENDERING_DEVICE_D3D11 m_device;
		std::unordered_map<uint32_t, WINDOW_CONTEXT_D3D11> m_window_contexts;
		COMMAND_LIST_D3D11 m_command_list;
	};
}
