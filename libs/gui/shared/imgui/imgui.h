
#pragma once

//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "core/shared/debugging/asserts.h"
#include "gui/shared/graphics/renderer/renderer.h"
#include "gui/shared/graphics/RHI/shader_base.h"

#include <gui/thirdparty/imgui/imgui.h>

//////////////////////////////////////////////////////////////////////
//! Forward Declerations
//////////////////////////////////////////////////////////////////////

namespace gui
{
	void initialise_platform_interface();
}

namespace gui
{
	inline void initialise( RENDERER& renderer, const float width, const float height )
	{
		renderer.create_shader( RendererShader::IMGUI_VERTEX, RHI_Shader_Type::RHI_Shader_Vertex, 
								core::RHI_Vertex_Type::RHI_Vertex_Type_Position2dTextureColor8, "imgui.hlsl" );
		renderer.create_shader( RendererShader::IMGUI_PIXEL, {}, {}, "imgui.hlsl" );

		auto& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_RendererHasViewports | ImGuiBackendFlags_RendererHasVtxOffset;
		io.BackendRendererName = "renderer";
		if ( io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable )
		{
			initialise_platform_interface();
		}
	}

	inline void Shutdown()
	{
		ImGui::DestroyPlatformWindows();
	}

	static void RHI_Window_Create( ImGuiViewport* viewport )
	{
		if ( !viewport )
		{
			ASSERT_FAILED( "Invalid viewport" );
			return;
		}

		/*viewport->RendererUserData = new RHI_SwapChain
		(
			viewport->PlatformHandle,
			g_rhi_device,
			static_cast<uint32_t>(viewport->Size.x),
			static_cast<uint32_t>(viewport->Size.y),
			RHI_Format_R8G8B8A8_Unorm,
			g_renderer->GetSwapChain()->GetBufferCount(),
			g_renderer->GetSwapChain()->GetFlags(),
			(string( "swapchain_child_" ) + string( to_string( viewport->ID ) )).c_str()
		);*/
	}

	static void RHI_Window_Destroy( ImGuiViewport* viewport )
	{
		/*RHI_SwapChain* swap_chain = GetSwapchain( viewport );
		if ( !swap_chain )
			return;

		sp_ptr_delete( swap_chain );
		viewport->RendererUserData = nullptr;*/
	}

	inline void initialise_platform_interface()
	{
		/*ImGuiPlatformIO& platform_io = ImGui::GetPlatformIO();
		platform_io.Renderer_CreateWindow = RHI_Window_Create;
		platform_io.Renderer_DestroyWindow = RHI_Window_Destroy;
		platform_io.Renderer_SetWindowSize = RHI_Window_SetSize;
		platform_io.Renderer_RenderWindow = RHI_Window_Render;
		platform_io.Renderer_SwapBuffers = RHI_Window_Present;*/
	}

}
