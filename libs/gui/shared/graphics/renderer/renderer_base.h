
#pragma once

//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include <memory>
#include <vector>

//////////////////////////////////////////////////////////////////////
//! Forward Declerations
//////////////////////////////////////////////////////////////////////

namespace engine
{
	class MESH;
	class WORLD;
}

namespace gui
{
	class RENDERING_DEVICE_BASE;
	enum class BUFFER_TYPE : uint8_t;

	struct WINDOW_CONTEXT
	{
		uint32_t width = 0;
		uint32_t height = 0;
	};

	class RENDERER_BASE
	{
	public:
		RENDERER_BASE();
		~RENDERER_BASE();

	protected:
		template<typename BUFFER, typename VERTEX>
		BUFFER* create_buffer( RENDERING_DEVICE_BASE& device, BUFFER_TYPE buffer_type, const std::vector<VERTEX>& vertices )
		{
			auto buffer{ std::make_unique<BUFFER>() };
			if ( buffer->create( device, buffer_type, vertices ) )
			{
				return buffer.release();
			}
			else
			{
				return nullptr;
			}
		}

		virtual void on_mesh_created( engine::MESH* ) = 0;

	private:
		void on_world_created( engine::WORLD* world );

		size_t m_on_world_created_id{};
	};
}
