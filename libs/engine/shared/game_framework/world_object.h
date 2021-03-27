//////////////////////////////////////////////////////////////////////
//! Copyright Alastair Melville
//////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "core/shared/vertex.h"

#include <memory>
#include <vector>

namespace engine
{
	class MESH;

	class WORLD_OBJECT
	{
	public:
		WORLD_OBJECT();
		~WORLD_OBJECT();
		WORLD_OBJECT( const engine::WORLD_OBJECT& other );

		void create_mesh( const std::vector<core::RHI_Vertex_PosTexNorTan>&& vertices, const std::vector<uint32_t>&& indices );

		MESH* get_mesh() const { return m_mesh.get(); }

	private:
		std::unique_ptr<MESH> m_mesh;
	};
}