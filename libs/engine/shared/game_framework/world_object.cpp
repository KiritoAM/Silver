//////////////////////////////////////////////////////////////////////
//! Copyright Alastair Melville
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "engine/shared/game_framework/world_object.h"

#include "engine/shared/game_framework/mesh.h"

namespace engine
{
	WORLD_OBJECT::WORLD_OBJECT() = default;

	WORLD_OBJECT::~WORLD_OBJECT() = default;

	WORLD_OBJECT::WORLD_OBJECT( const engine::WORLD_OBJECT& ) {}

	void WORLD_OBJECT::create_mesh( std::vector<core::RHI_Vertex_PosTexNorTan>&& vertices, std::vector<uint32_t>&& indices, gui::MATERIAL* material )
	{
		m_mesh = std::make_unique<MESH>( std::move( vertices ), std::move( indices ), material );
	}
}