//////////////////////////////////////////////////////////////////////
//! Copyright Alastair Melville
//////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "gui/shared/screen.h"

#include "core/shared/math/rectangle.h"
#include "gui/shared/window/window.h"
#include "gui/shared/ui/widgets/containers/container.h"

namespace gui
{
	SCREEN::SCREEN()
		: m_window{ std::make_unique<WINDOW>() }
	{}

	SCREEN::~SCREEN() = default;

	void SCREEN::paint()
	{
		m_root_widget->temp();
	}
}
