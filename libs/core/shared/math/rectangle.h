//////////////////////////////////////////////////////////////////////
//! Copyright Alastair Melville
//////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "core/shared/math/vector4d.h"

#include "core/shared/math/vector2d.h"

namespace core
{
	template<typename TYPE>
	struct RECTANGLE : public VECTOR4D<TYPE>
	{
		using super = VECTOR4D<TYPE>;
		using super::X;
		using super::Y;
		using super::Z;
		using super::A;

		RECTANGLE() = default;

		RECTANGLE(TYPE InX, TYPE InY, TYPE InZ, TYPE InA)
		{
			X = InX;
			super::Y = InY;
			super::Z = InZ;
			super::A = InA;
		}

		static const RECTANGLE<TYPE> ZERO_VALUE;

		TYPE get_left() const { return X; }
		TYPE get_right() const { return X + get_width(); }
		TYPE get_width() const { return Z; }

		TYPE get_top() const { return Y; }
		TYPE get_bottom() const { return Y + get_height(); }
		TYPE get_height() const { return A; }

		VECTOR2D<TYPE> get_top_left() const
		{
			return {get_left(), get_top()};
		}

		VECTOR2D<TYPE> get_top_right() const
		{
			return { get_right(), get_top() };
		}

		VECTOR2D<TYPE> get_bottom_left() const
		{
			return { get_left(), get_bottom() };
		}

		VECTOR2D<TYPE> get_bottom_right() const
		{
			return { get_right(), get_bottom() };
		}

		VECTOR2D<TYPE> get_dimensions() const
		{
			return { get_width(), get_height() };
		}
	};

	template<typename TYPE>
	const RECTANGLE<TYPE> RECTANGLE<TYPE>::ZERO_VALUE = RECTANGLE<TYPE>(TYPE(), TYPE());

	using FRECTANGLE = RECTANGLE<float>;
}
