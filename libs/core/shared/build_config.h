
#pragma once

namespace core
{
	constexpr bool is_debug()
	{
#if DEBUG
		return true;
#else
		return false;
#endif
	}

	constexpr bool is_editor()
	{
#if EDITOR
		return true;
#else
		return false;
#endif
	}
}
