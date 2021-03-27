

//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "gui/platforms/graphics/RHI/windows/d3d11/RHI_context_d3d11.h"

#include "core/shared/math/vector3d.h"
#include "gui/platforms/graphics/RHI/windows/d3d11/buffer_d3d11.h"
#include "gui/platforms/graphics/RHI/windows/d3d11/pipeline_state_d3d11.h"
#include "gui/platforms/graphics/RHI/windows/d3d11/shader_d3d11.h"
#include "gui/shared/graphics/RHI/input_layout.h"
#include "gui/shared/graphics/RHI/viewport.h"

#include <d3d11.h>

namespace gui
{
	bool RENDERING_CONTEXT_D3D11::begin_render_pass( const PIPELINE_STATE_D3D11& pipeline_state )
	{
		// Vertex shader
		{
			// New state
			ID3D11VertexShader* shader = static_cast<ID3D11VertexShader*>(pipeline_state.m_vertex_shader ? pipeline_state.m_vertex_shader->GetResource() : nullptr);

			// Current state
			ID3D11VertexShader* set_shader = nullptr;
			UINT instance_count = 256;
			ID3D11ClassInstance* instances[256];
			m_device_context->VSGetShader( &set_shader, instances, &instance_count );

			// Set if dirty
			if ( set_shader != shader )
			{
				m_device_context->VSSetShader( shader, nullptr, 0u );
			}
		}

		// Vertex Shader Input layout
		{
			// New state
			ID3D11InputLayout* input_layout = static_cast<ID3D11InputLayout*>(pipeline_state.m_vertex_shader ? pipeline_state.m_vertex_shader->get_input_layout()->GetResource() : nullptr);

			// Current state
			ID3D11InputLayout* input_layout_set = nullptr;
			m_device_context->IAGetInputLayout( &input_layout_set );

			// Set if dirty
			if ( input_layout_set != input_layout )
			{
				m_device_context->IASetInputLayout( input_layout );
			}
		}

		// Pixel shader
		{
			// New state
			ID3D11PixelShader* shader = static_cast<ID3D11PixelShader*>(pipeline_state.m_pixel_shader ? pipeline_state.m_pixel_shader->GetResource() : nullptr);

			// Current state
			ID3D11PixelShader* set_shader = nullptr; UINT instance_count = 256; ID3D11ClassInstance* instances[256];
			m_device_context->PSGetShader( &set_shader, instances, &instance_count );

			// Set if dirty
			if ( set_shader != shader )
			{
				m_device_context->PSSetShader( shader, nullptr, 0 );
			}
		}

		// Compute shader
		{
			// New state
			ID3D11ComputeShader* shader = static_cast<ID3D11ComputeShader*>(pipeline_state.m_compute_shader ? pipeline_state.m_compute_shader->GetResource() : nullptr);

			// Current state
			ID3D11ComputeShader* set_shader = nullptr; UINT instance_count = 256; ID3D11ClassInstance* instances[256];
			m_device_context->CSGetShader( &set_shader, instances, &instance_count );

			// Set if dirty
			if ( set_shader != shader )
			{
				m_device_context->CSSetShader( shader, nullptr, 0 );
			}
		}

		// Primitive topology
		if ( pipeline_state.primitive_topology != RHI_PrimitiveTopology_Unknown )
		{
			// New state
			const D3D11_PRIMITIVE_TOPOLOGY topology = d3d11_primitive_topology[pipeline_state.primitive_topology];

			// Current state
			D3D11_PRIMITIVE_TOPOLOGY topology_set;
			m_device_context->IAGetPrimitiveTopology( &topology_set );

			// Set if dirty
			if ( topology_set != topology )
			{
				m_device_context->IASetPrimitiveTopology( d3d11_primitive_topology[pipeline_state.primitive_topology] );
			}
		}

		// Viewport
		if ( pipeline_state.m_viewport.is_valid() )
		{
			set_viewport( pipeline_state.m_viewport );
		}

		return true;
	}

	void RENDERING_CONTEXT_D3D11::clear_render_target_view( ID3D11RenderTargetView* render_target_view, const core::VECTOR3D<float>& rgb )
	{
		const float colour[] { rgb.X, rgb.Y, rgb.Z, 1.0f };
		m_device_context->ClearRenderTargetView( render_target_view, colour );
	}

	void RENDERING_CONTEXT_D3D11::set_viewport( const VIEWPORT& viewport ) const
	{
		const auto top_left = viewport.m_area.get_top_left();

		D3D11_VIEWPORT d3d11_viewport;
		d3d11_viewport.TopLeftX = top_left.X;
		d3d11_viewport.TopLeftY = top_left.Y;
		d3d11_viewport.Width = viewport.m_area.get_width();
		d3d11_viewport.Height = viewport.m_area.get_height();
		d3d11_viewport.MinDepth = viewport.m_min_depth;
		d3d11_viewport.MaxDepth = viewport.m_max_depth;

		m_device_context->RSSetViewports( 1, &d3d11_viewport );
	}

	void RENDERING_CONTEXT_D3D11::set_vertex_buffer( BUFFER_D3D11& buffer_d3d11, uint32_t offset )
	{
		ID3D11Buffer* vertex_buffer = buffer_d3d11.GetResource();

		if ( !vertex_buffer )
		{
			ASSERT_SHOULDNT_BE_HERE();
			return;
		}

		UINT stride = buffer_d3d11.GetStride();
		UINT offsets = offset;

		// Get currently set buffer
		ID3D11Buffer* set_buffer = nullptr;
		UINT set_stride = buffer_d3d11.GetStride();
		UINT set_offset = 0;
		m_device_context->IAGetVertexBuffers( 0, 1, &set_buffer, &set_stride, &set_offset );

		// Skip if the same vertex buffer is already set
		if ( set_buffer != vertex_buffer || set_offset != offset )
		{
			m_device_context->IASetVertexBuffers( 0, 1, &vertex_buffer, &stride, &offsets );
		}
	}

	bool RENDERING_CONTEXT_D3D11::draw( const uint32_t vertex_count, const uint32_t vertex_offset )
	{
		m_device_context->Draw( vertex_count, vertex_offset );

		return true;
	}

	bool RENDERING_CONTEXT_D3D11::draw_indexed( const uint32_t index_count, const uint32_t index_offset, const uint32_t vertex_offset )
	{
		m_device_context->DrawIndexed( static_cast<UINT>(index_count), static_cast<UINT>(index_offset), static_cast<INT>(vertex_offset) );

		return true;
	}
}