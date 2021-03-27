
#pragma once

//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "gui/shared/graphics/RHI/RHI_swapchain _base.h"

#include "gui/shared/graphics/RHI/RHI_types.h"

#include <d3d11.h>
#include <wrl/client.h>

namespace wrl = Microsoft::WRL;

//////////////////////////////////////////////////////////////////////
//! Forward Decelerations
//////////////////////////////////////////////////////////////////////

namespace core
{
	template<typename TYPE>
	struct VECTOR3D;
}

namespace gui
{
	class RENDERING_DEVICE_D3D11;

	class SWAPCHAIN_D3D11 : public SWAPCHAIN_BASE
	{
	public:
		SWAPCHAIN_D3D11(
			HWND window_handle,
			RENDERING_DEVICE_D3D11& rhi_device,
			uint32_t width,
			uint32_t height,
			RHI_Format format,
			uint32_t flags,
			const char* name
		);

		SWAPCHAIN_D3D11& operator = ( const SWAPCHAIN_D3D11& other ) = default;

		ID3D11RenderTargetView* Get_Resource_View_RenderTarget()  const { return m_render_target_view.Get(); }

		void clear_backbuffer( const core::VECTOR3D<float>& rgb );

		void present();

	//private:
		RENDERING_DEVICE_D3D11& m_device;
		wrl::ComPtr<IDXGISwapChain> m_swapchain;
		wrl::ComPtr<ID3D11RenderTargetView> m_render_target_view;
	};
}
