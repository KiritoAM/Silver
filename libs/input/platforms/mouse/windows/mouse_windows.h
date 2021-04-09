//////////////////////////////////////////////////////////////////////
//! Copyright Alastair Melville
//////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "input/shared/mouse/mouse_base.h"

#include <memory>
#include <stdint.h>
#include <Windows.h>

namespace input
{
	class MOUSE_WINDOWS : public MOUSE_BASE
	{
		using super = MOUSE_BASE;

	public:
		bool handle_message(HWND in_window, uint32_t in_message, WPARAM in_wparam, LPARAM in_lparam);

	protected:
		MOUSE_WINDOWS();
		~MOUSE_WINDOWS();

		void on_mouse_moved() override;

		void on_mouse_button_down(BUTTON in_pressed_button) override;
		void on_mouse_button_up(BUTTON in_released_button) override;

	private:
		void handle_absolute_input();

		bool handle_raw_input();

		struct impl;
		std::unique_ptr<impl> m_impl{ nullptr };
	};
}