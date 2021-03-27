//////////////////////////////////////////////////////////////////////
//! Copyright Alastair Melville
//////////////////////////////////////////////////////////////////////

#pragma once

namespace core
{
	template<typename TYPE>
	struct VECTOR2D;
}

namespace input
{
	enum class EINPUT_TYPE : uint8_t;

	using MOUSE_AXIS_TYPE = uint32_t;
	using MOUSE_POS_TYPE = core::VECTOR2D<MOUSE_AXIS_TYPE>;
}