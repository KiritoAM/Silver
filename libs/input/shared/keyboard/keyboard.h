//////////////////////////////////////////////////////////////////////
//! Copyright Alastair Melville
//////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "core/shared/patterns/automatic_singleton.h"

#if PLATFORM_WINDOWS
#include "input/platforms/keyboard/windows/keyboard_windows.h"
using KEYBOARD_PLATFORM = input::KEYBOARD_WINDOWS;
#endif

namespace input
{
	class KEYBOARD : public KEYBOARD_PLATFORM, public core::AUTOMATIC_SINGLETON<KEYBOARD>
	{
	public:
		using KEYBOARD_PLATFORM::handle_message;

		void on_key_down(KEY in_key) override;
		void on_key_down(KEY in_key, const WINDOWS_KEYS_STATE& in_windows_keys_state) override;

		void on_key_up(KEY in_key) override;

	//private:
		friend core::AUTOMATIC_SINGLETON<KEYBOARD>;
		KEYBOARD() = default;
		~KEYBOARD() override = default;
	};
}