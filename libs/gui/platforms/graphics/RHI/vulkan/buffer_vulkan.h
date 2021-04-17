
#pragma once

//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "gui/shared/graphics/RHI/buffer_base.h"

namespace gui
{
	class RENDERING_DEVICE_VULKAN;

	class BUFFER_VULKAN : public BUFFER_BASE
	{
	public:
		void* Map( RENDERING_DEVICE_VULKAN& device );

		bool Unmap( RENDERING_DEVICE_VULKAN& device );

		ID3D11Buffer* GetResource() const { return m_buffer.Get(); }

	private:
		bool _create( RENDERING_DEVICE_BASE& device, BUFFER_TYPE buffer_type, const void* vertices ) override;

		void _destroy();

		bool m_persistent_mapping = true; // only affects Vulkan
		void* m_mapped = nullptr;
	};
}
