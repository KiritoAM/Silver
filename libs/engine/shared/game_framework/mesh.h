//////////////////////////////////////////////////////////////////////
//! Copyright Alastair Melville
//////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "core/shared/vertex.h"

#include <vector>

namespace engine
{
	class MESH
	{
	public:
		MESH( const std::vector<core::RHI_Vertex_PosTexNorTan>&& vertices, const std::vector<uint32_t>&& indices );
		~MESH() = default;

		const std::vector<core::RHI_Vertex_PosTexNorTan>& get_vertices() const { return m_vertices; }

		const std::vector<uint32_t>& get_indices() const { return m_indices; }

	private:
		std::vector<core::RHI_Vertex_PosTexNorTan> m_vertices;
		std::vector<uint32_t> m_indices;
	};
}