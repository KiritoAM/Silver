
#pragma once

//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "engine/shared/application/application.h"

namespace app
{
	class GAME_APPLICATION : public engine::APPLICATION
	{
	public:
		void startup() override;

	private:
		void initialise_libraries();
	};
}
