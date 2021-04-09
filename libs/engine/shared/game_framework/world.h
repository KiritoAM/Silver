//////////////////////////////////////////////////////////////////////
//! Copyright Alastair Melville
//////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "engine/shared/game_framework/nodes/node.h"

#include "core/shared/patterns/instance_tracker.h"
#include "engine/shared/game_framework/level.h"

#include <vector>

namespace engine
{
	class MESH;

	inline constexpr auto PERSISTENT_LEVEL_INDEX{ 0 };

	class WORLD : public NODE
	{
	public:
		WORLD();
		~WORLD();

		bool receive_event( const engine::EVENT& in_event ) override;

		void Tick(float InDeltaTime);

		void create_world_object();

		void create_world_object( const std::string& mesh_filepath );

		void create_world_object( std::vector<core::RHI_Vertex_PosTexNorTan>&& vertices, std::vector<uint32_t>&& indices );

		static WORLD* get_world();

		inline static LEVEL* s_current_level{ nullptr };

		core::MULTICAST_DELEGATE_ONE_PARAM<void, MESH*> m_on_mesh_created;

		std::vector<LEVEL> m_levels;
	};
}