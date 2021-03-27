//////////////////////////////////////////////////////////////////////
//! Copyright Alastair Melville
//////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "core/shared/patterns/non_automatic_singleton.h"

#include <memory>
#include <unordered_map>

//////////////////////////////////////////////////////////////////////
//! Forward Declerations
//////////////////////////////////////////////////////////////////////

namespace gui
{
	class SCREEN;
}

namespace gui
{
	inline constexpr uint32_t MAIN_SCREEN_ID{ 0 };

	class SCREEN_MANAGER : public core::NON_AUTOMATIC_SINGLETON<SCREEN_MANAGER>
	{
		friend class core::NON_AUTOMATIC_SINGLETON<SCREEN_MANAGER>;

	public:
		~SCREEN_MANAGER();

		uint32_t create_window();

		SCREEN* get_screen( uint32_t screen_id ) const { return m_screens.at( screen_id ).get(); }
		
	protected:
		SCREEN_MANAGER();
		

		void tick();

		std::unordered_map< uint32_t, std::unique_ptr<SCREEN> > m_screens;
	};
}
