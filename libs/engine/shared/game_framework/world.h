//////////////////////////////////////////////////////////////////////
//! Copyright Alastair Melville
//////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "core/shared/patterns/instance_tracker.h"
#include "engine/shared/game_framework/level.h"

#include <vector>

namespace engine
{
	class MESH;

	inline constexpr auto PERSISTENT_LEVEL_INDEX{ 0 };

	class WORLD
	{
	public:
		WORLD();
		~WORLD();

		void Tick(float InDeltaTime);

		void create_world_object();

		void create_world_object( const std::string& mesh_filepath );

		/*template<typename TYPE, typename... ARGS>
		static TYPE* spawn_actor(LEVEL* in_level_override = nullptr, ARGS&& ... in_args);*/

		static WORLD* get_world();

		inline static LEVEL* s_current_level{ nullptr };

		core::MULTICAST_DELEGATE_ONE_PARAM<void, MESH*> m_on_mesh_created;

		std::vector<LEVEL> m_levels;
	};

	//template<typename TYPE, typename... ARGS>
	//inline TYPE* WORLD::spawn_actor(LEVEL* in_level_override, ARGS&& ... in_args)
	//{
	//	// todo assert if doesn't inherit from WORLD_OBJECT
	//	return NewObject<TYPE>(new TYPE( std::forward<ARGS>(in_args)... ), in_level_override ? (OBJECT*)in_level_override : (OBJECT*)s_current_level); // TEMP non-implicit converstion
	//}
}