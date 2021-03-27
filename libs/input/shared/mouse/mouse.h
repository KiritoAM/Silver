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
using POINTING_DEVICE_PLATFORM = input::POINTING_DEVICE_WINDOWS;
#endif

namespace input
{
	class POINTING_DEVICE : public POINTING_DEVICE_PLATFORM, public core::AUTOMATIC_SINGLETON<POINTING_DEVICE>
	{
		using super = POINTING_DEVICE_PLATFORM;

		using DELEGATE_TYPE = core::MULTICAST_DELEGATE_ONE_PARAM<void, POINTING_DEVICE*>;
		using MOVE_DELEGATE_TYPE = core::MULTICAST_DELEGATE_TWO_PARAMS<void, MOUSE_POS_TYPE, MOUSE_POS_TYPE>;

	public:
		using POINTING_DEVICE_PLATFORM::handle_message;

		DELEGATE_TYPE& get_pointing_device_delegate() { return m_pointing_device_delegate; }
		MOVE_DELEGATE_TYPE& get_on_moved_delegate() { return m_on_moved_delegate; }

	private:
		using POINTING_DEVICE_PLATFORM::on_mouse_moved;

		void on_mouse_moved() override;

		DELEGATE_TYPE m_pointing_device_delegate;
		MOVE_DELEGATE_TYPE m_on_moved_delegate;
	};
}