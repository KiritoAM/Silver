

#include "engine/shared/application/application.h"

#include "engine/shared/game_framework/world.h"

namespace engine
{
	/*ENGINE* ENGINE::create_singleton_custom()
	{
		return new UGameEngine;
	}*/

	APPLICATION::APPLICATION()
	{
		m_game_instances.try_emplace( MAIN_INSTANCE_ID );

		m_engine_start_time = std::chrono::system_clock::now();
		m_last_time = m_engine_start_time;
	}

	void APPLICATION::run_loop()
	{
		startup();

		while ( !m_should_shutdown )
		{
			iteration();
		}

		shutdown();
	}

	void APPLICATION::startup()
	{

	}

	void APPLICATION::iteration()
	{
		const auto current_time = std::chrono::system_clock::now();
		m_delta_time = current_time - m_last_time;
		m_last_time = current_time;

		process_os_messages();

		/*if (WorldList[0] && WorldList[0]->get_current_world())
		{
			WorldList[0]->get_current_world()->Tick(in_delta_time);
		}*/
	}

	void APPLICATION::shutdown()
	{

	}
}