

//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "gui/platforms/graphics/RHI/windows/d3d11/RHI_swapchain_d3d11.h"

#include "core/shared/debugging/asserts.h"
#include "core/shared/math/vector3d.h"
#include "gui/platforms/graphics/RHI/windows/d3d11/RHI_context_d3d11.h"
#include "gui/platforms/graphics/RHI/windows/d3d11/RHI_device_d3d11.h"

#include <dxgi1_5.h>
#include <dxgiformat.h>

namespace
{
	constexpr DXGI_FORMAT d3d11_format[] =
	{
		// R
		DXGI_FORMAT_R8_UNORM,
		DXGI_FORMAT_R16_UINT,
		DXGI_FORMAT_R16_FLOAT,
		DXGI_FORMAT_R32_UINT,
		DXGI_FORMAT_R32_FLOAT,
		// RG
		DXGI_FORMAT_R8G8_UNORM,
		DXGI_FORMAT_R16G16_FLOAT,
		DXGI_FORMAT_R32G32_FLOAT,
		// RGB
		DXGI_FORMAT_R11G11B10_FLOAT,
		DXGI_FORMAT_R32G32B32_FLOAT,
		// RGBA
		DXGI_FORMAT_R8G8B8A8_UNORM,
		DXGI_FORMAT_R10G10B10A2_UNORM,
		DXGI_FORMAT_R16G16B16A16_SNORM,
		DXGI_FORMAT_R16G16B16A16_FLOAT,
		DXGI_FORMAT_R32G32B32A32_FLOAT,
		// Depth
		DXGI_FORMAT_D32_FLOAT,
		DXGI_FORMAT_D32_FLOAT_S8X24_UINT,

		DXGI_FORMAT_UNKNOWN
	};

	// Determines whether tearing support is available for fullscreen borderless windows.
	inline bool CheckTearingSupport( const gui::RENDERING_DEVICE_D3D11& device )
	{
		// Rather than create the 1.5 factory interface directly, we create the 1.4
		// interface and query for the 1.5 interface. This will enable the graphics
		// debugging tools which might not support the 1.5 factory interface
		wrl::ComPtr<IDXGIFactory4> factory4;
		HRESULT resut = CreateDXGIFactory1( IID_PPV_ARGS( factory4.GetAddressOf() ) );
		BOOL allowTearing = FALSE;
		if ( SUCCEEDED( resut ) )
		{
			wrl::ComPtr<IDXGIFactory5> factory5;
			resut = factory4.As( &factory5 );
			if ( SUCCEEDED( resut ) )
			{
				resut = factory5->CheckFeatureSupport( DXGI_FEATURE_PRESENT_ALLOW_TEARING, &allowTearing, sizeof( allowTearing ) );
			}
		}

		const bool fullscreen_borderless_support = SUCCEEDED( resut ) && allowTearing;
		const bool vendor_support = !device.GetPrimaryPhysicalDevice()->IsIntel(); // Intel, bad

		return fullscreen_borderless_support && vendor_support;
	}

	inline uint32_t validate_flags( const gui::RENDERING_DEVICE_D3D11& device, uint32_t flags )
	{
		// If SwapChain_Allow_Tearing was requested
		if ( flags & gui::RHI_Present_Mode::RHI_Present_Immediate )
		{
			// Check if the adapter supports it, if not, disable it (tends to fail with Intel adapters)
			if ( !CheckTearingSupport( device ) )
			{
				flags &= ~gui::RHI_Present_Immediate;
				//LOG_WARNING( "Present_Immediate was requested but it's not supported by the adapter." );
			}
		}

		return flags;
	}

	inline UINT get_flags( uint32_t flags )
	{
		UINT d3d11_flags = 0;

		d3d11_flags |= flags & gui::RHI_SwapChain_Allow_Mode_Switch ? DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH : 0;
		d3d11_flags |= flags & gui::RHI_Present_Immediate ? DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING : 0;

		return d3d11_flags;
	}

	inline DXGI_SWAP_EFFECT get_swap_effect( const gui::RENDERING_DEVICE_D3D11& device, uint32_t flags )
	{
#if !defined(_WIN32_WINNT_WIN10)
		if ( flags & RHI_Swap_Flip_Discard )
		{
			//LOG_WARNING( "Swap_Flip_Discard was requested but it's only supported in Windows 10, using Swap_Discard instead." );
			flags &= ~RHI_Swap_Flip_Discard;
			flags |= RHI_Swap_Discard;
		}
#endif

		if ( flags & gui::RHI_Swap_Flip_Discard && device.GetPrimaryPhysicalDevice()->IsIntel() )
		{
			//LOG_WARNING( "Swap_Flip_Discard was requested but it's not supported by Intel adapters, using Swap_Discard instead." );
			flags &= ~gui::RHI_Swap_Flip_Discard;
			flags |= gui::RHI_Swap_Discard;
		}

		if ( flags & gui::RHI_Swap_Discard )           return DXGI_SWAP_EFFECT_DISCARD;
		if ( flags & gui::RHI_Swap_Sequential )        return DXGI_SWAP_EFFECT_SEQUENTIAL;
		if ( flags & gui::RHI_Swap_Flip_Discard )      return DXGI_SWAP_EFFECT_FLIP_DISCARD;
		if ( flags & gui::RHI_Swap_Flip_Sequential )   return DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;

		ASSERT_FAILED( "Unable to determine the requested swap effect, opting for DXGI_SWAP_EFFECT_DISCARD" );
		return DXGI_SWAP_EFFECT_DISCARD;
	}
}

namespace gui
{
	SWAPCHAIN_D3D11::SWAPCHAIN_D3D11(
		HWND window_handle,
		RENDERING_DEVICE_D3D11& rhi_device,
		const uint32_t width,
		const uint32_t height,
		RHI_Format format = RHI_Format_R8G8B8A8_Unorm,
		uint32_t flags = RHI_Present_Immediate,
		const char* name = nullptr
	)
		: m_device{ rhi_device }
	{
		// Validate device
		if ( !rhi_device.get_device() )
		{
			ASSERT_FAILED( "Invalid device." );
			return;
		}

		// Validate window handle
		if ( !window_handle || !IsWindow( window_handle ) )
		{
			ASSERT_FAILED( "Invalid window." );
			return;
		}

		// Validate resolution
		if ( !rhi_device.ValidateResolution( width, height ) )
		{
			//LOG_WARNING( "%dx%d is an invalid resolution", width, height );
			return;
		}

		// Get factory
		wrl::ComPtr<IDXGIFactory> dxgi_factory;
		if ( const auto& adapter = rhi_device.GetPrimaryPhysicalDevice() )
		{
			auto dxgi_adapter = static_cast<IDXGIAdapter*>(adapter->GetData());
			if ( dxgi_adapter->GetParent( IID_PPV_ARGS( dxgi_factory.GetAddressOf() ) ) != S_OK )
			{
				ASSERT_FAILED( "Failed to get adapter's factory" );
				return;
			}
		}
		else
		{
			ASSERT_FAILED( "Invalid primary adapter" );
			return;
		}

		m_format = format;
		m_buffer_count = s_swap_chain_buffer_count;
		m_windowed = true;
		m_width = width;
		m_height = height;
		m_flags = validate_flags( m_device, flags );

		// Create swap chain
		DXGI_SWAP_CHAIN_DESC desc = {};
		desc.BufferCount = static_cast<UINT>(m_buffer_count);
		desc.BufferDesc.Width = static_cast<UINT>(width);
		desc.BufferDesc.Height = static_cast<UINT>(height);
		desc.BufferDesc.Format = d3d11_format[format];
		desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc.OutputWindow = window_handle;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Windowed = m_windowed;
		desc.SwapEffect = get_swap_effect( m_device, m_flags );
		desc.Flags = get_flags( m_flags );

		if ( FAILED( dxgi_factory->CreateSwapChain( m_device.get_device(), &desc, m_swapchain.GetAddressOf() ) ) )
		{
			ASSERT_FAILED( "Failed to create swapchain" );
			return;
		}

		// Create the render target
		wrl::ComPtr<ID3D11Texture2D> backbuffer;
		auto result = m_swapchain->GetBuffer( 0, IID_PPV_ARGS( backbuffer.GetAddressOf() ) );
		if ( FAILED( result ) )
		{
			//ASSERT_FAILED( "%s", dxgi_error_to_string( result ) );
			return;
		}

		result = m_device.get_device()->CreateRenderTargetView( backbuffer.Get(), nullptr, m_render_target_view.GetAddressOf() );
		if ( FAILED( result ) )
		{
			//ASSERT_FAILED( "%s", d3d11_utility::dxgi_error_to_string( result ) );
			return;
		}

		// Create command lists
		for ( uint32_t i = 0; i < m_buffer_count; ++i )
		{
			//m_cmd_lists.emplace_back( make_shared<RHI_CommandList>( i, this, rhi_device->get_context()->device_context ) );
		}

		//m_cmd_index = 0;
	}

	void SWAPCHAIN_D3D11::clear_backbuffer( const core::VECTOR3D<float>& rgb )
	{
		m_device.get_context()->clear_render_target_view( m_render_target_view.Get(), rgb );
	}

	void SWAPCHAIN_D3D11::present()
	{
		m_swapchain->Present( 1u, 0u );
	}
}
