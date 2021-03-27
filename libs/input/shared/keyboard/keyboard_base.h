//////////////////////////////////////////////////////////////////////
//! Copyright Alastair Melville
//////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////


namespace input
{
	enum class KEY : uint8_t;
	struct WINDOWS_KEYS_STATE;
}

namespace input
{
	class KEYBOARD_BASE
	{
	protected:
		KEYBOARD_BASE() = default;
		virtual ~KEYBOARD_BASE() = default;

		virtual void on_key_down(KEY in_key) = 0;
		virtual void on_key_down(KEY in_key, const WINDOWS_KEYS_STATE& in_windows_keys_state) = 0;

		virtual void on_key_up(KEY in_key) = 0;
	};
}