//////////////////////////////////////////////////////////////////////
//! Copyright Alastair Melville
//////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include <memory>

//////////////////////////////////////////////////////////////////////
//! Forward Declerations
//////////////////////////////////////////////////////////////////////

namespace gui
{
	class CONTAINER;
	class WINDOW;
}

namespace gui
{
	class SCREEN
	{
	public:
		SCREEN();
		~SCREEN();

		void paint();

		WINDOW* get_window() const { return m_window.get(); }

	private:
		std::unique_ptr<WINDOW> m_window;

		std::unique_ptr<CONTAINER> m_root_widget;
	};
}
