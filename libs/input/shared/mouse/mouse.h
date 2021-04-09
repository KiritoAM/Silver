//////////////////////////////////////////////////////////////////////
//! Copyright Alastair Melville
//////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "core/shared/patterns/automatic_singleton.h"

#include "core/shared/patterns/delegate.h"

#if PLATFORM_WINDOWS
#include "input/platforms/mouse/windows/mouse_windows.h"
using MOUSE_PLATFORM = input::MOUSE_WINDOWS;
#endif

namespace input
{
	class MOUSE_DEVICE : public MOUSE_PLATFORM, public core::AUTOMATIC_SINGLETON<MOUSE_DEVICE>
	{
		using super = MOUSE_PLATFORM;

		using DELEGATE_TYPE = core::MULTICAST_DELEGATE_ONE_PARAM<void, MOUSE_DEVICE*>;
		using MOVE_DELEGATE_TYPE = core::MULTICAST_DELEGATE_TWO_PARAMS<void, MOUSE_POS_TYPE, MOUSE_POS_TYPE>;

	public:
		using MOUSE_PLATFORM::handle_message;

		DELEGATE_TYPE& get_pointing_device_delegate() { return m_pointing_device_delegate; }
		MOVE_DELEGATE_TYPE& get_on_moved_delegate() { return m_on_moved_delegate; }

	private:
		using MOUSE_PLATFORM::on_mouse_moved;

		void on_mouse_moved() override;

		DELEGATE_TYPE m_pointing_device_delegate;
		MOVE_DELEGATE_TYPE m_on_moved_delegate;
	};
}