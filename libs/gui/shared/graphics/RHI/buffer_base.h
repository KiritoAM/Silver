
#pragma once

//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include <vector>

namespace gui
{
	class RENDERING_DEVICE_BASE;
	enum class BUFFER_TYPE : uint8_t;

	class BUFFER_BASE
	{
	public:
		template<typename T>
		bool create( RENDERING_DEVICE_BASE& device, BUFFER_TYPE buffer_type, const std::vector<T>& vertices )
		{
			m_stride = static_cast<uint32_t>(sizeof( T ));
			m_count = static_cast<uint32_t>(vertices.size());
			m_total_size = m_stride * m_count;
			return _create( device, buffer_type, static_cast<const void*>(vertices.data()) );
		}

		uint32_t GetStride() const { return m_stride; }
		uint32_t GetCount() const { return m_count; }

	protected:
		virtual bool _create( RENDERING_DEVICE_BASE& device, BUFFER_TYPE buffer_type, const void* vertices ) = 0;

		uint32_t m_stride = 0;
		uint32_t m_count = 0;
		uint32_t m_total_size = 0;
	};
}
