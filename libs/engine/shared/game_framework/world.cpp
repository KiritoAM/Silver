//////////////////////////////////////////////////////////////////////
//! Copyright Alastair Melville
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "engine/shared/game_framework/world.h"

#include "core/shared/patterns/instance_tracker.h"

namespace engine
{
	WORLD::WORLD()
	{
		s_current_level = &m_levels.emplace_back();

		core::INSTANCE_TRACKER<WORLD>::add_instance( this );
	}

	WORLD::~WORLD()
	{
		core::INSTANCE_TRACKER<WORLD>::remove_instance( this );
	}

	void WORLD::Tick(float InDeltaTime)
	{

	}

	void WORLD::create_world_object()
	{

	}

	void WORLD::create_world_object( const std::string& mesh_filepath )
	{
		WORLD_OBJECT& world_object = s_current_level->m_world_objects.emplace_back();
		world_object.create_mesh( { {0.0f, 0.5f}, {0.5f, -0.5f}, {-0.5f, -0.5f} }, { 0, 1, 2 } );
		m_on_mesh_created.m_inner.execute<void, MESH*>( world_object.get_mesh() );
	}

	WORLD* WORLD::get_world()
	{
		return s_current_level ? s_current_level->OwningWorld : nullptr;
	}
}