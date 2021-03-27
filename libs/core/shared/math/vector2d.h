//////////////////////////////////////////////////////////////////////
//! Copyright Alastair Melville
//////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include <cmath>

namespace core
{
	template<typename TYPE>
	struct VECTOR2D
	{
	public:
		VECTOR2D() = default;

		VECTOR2D(TYPE InX, TYPE InY)
			: X(InX)
			, Y(InY)
		{}

		float get_size() const
		{
			return sqrtf(X * X + Y * Y);
		}

		static VECTOR2D direction_between_points(const VECTOR2D& in_first, const VECTOR2D& in_last)
		{
			const VECTOR2D diff(in_first - in_last);
			return /*std::atan2(*/VECTOR2D{ diff.Y, diff.X }; // todo normalise
		}

		VECTOR2D operator - (const VECTOR2D& other) const
		{
			return VECTOR2D(X - other.X, Y - other.Y);
		}

		bool operator == (const VECTOR2D& in_other) const
		{
			return X == in_other.X && Y == in_other.Y;
		}

		bool operator != (const VECTOR2D& in_other) const
		{
			return !operator==(in_other);
		}

		static const VECTOR2D<TYPE> ZERO_VALUE;

		/** VECTOR's X component. */
		TYPE X{};

		/** VECTOR's Y component. */
		TYPE Y{};
	};

	template<typename TYPE>
	const VECTOR2D<TYPE> VECTOR2D<TYPE>::ZERO_VALUE = VECTOR2D<TYPE>(TYPE(), TYPE());

	using FVECTOR2D = VECTOR2D<float>;
}
