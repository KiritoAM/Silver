
#pragma once

//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "gui/shared/graphics/RHI/RHI_device_base.h"

#include <memory>

namespace gui
{
	struct RENDERING_CONTEXT_VULKAN;
	enum RHI_Queue_Type;

	class RENDERING_DEVICE_VULKAN : public RENDERING_DEVICE_BASE
	{
	public:
		RENDERING_DEVICE_VULKAN();
		~RENDERING_DEVICE_VULKAN();

		RENDERING_CONTEXT_VULKAN* get_context() const { return m_context.get(); }

	private:
		void set_api_version();

		bool create_instance();

		bool create_device();

		void* Queue_Get( RHI_Queue_Type type ) const;

		uint32_t Queue_Index( const RHI_Queue_Type type ) const;

		bool Queue_Wait( RHI_Queue_Type type ) const;

		bool Queue_WaitAll() const;

		std::unique_ptr<RENDERING_CONTEXT_VULKAN> m_context;
	};
}
