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
			: x(InX)
			, y(InY)
		{}

		float get_size() const
		{
			return sqrtf(x * x + y * y);
		}

		static VECTOR2D direction_between_points(const VECTOR2D& in_first, const VECTOR2D& in_last)
		{
			const VECTOR2D diff(in_first - in_last);
			return /*std::atan2(*/VECTOR2D{ diff.y, diff.x }; // todo normalise
		}

		VECTOR2D operator - (const VECTOR2D& other) const
		{
			return VECTOR2D(x - other.x, y - other.y);
		}

		bool operator == (const VECTOR2D& in_other) const
		{
			return x == in_other.x && y == in_other.y;
		}

		bool operator != (const VECTOR2D& in_other) const
		{
			return !operator==(in_other);
		}

		bool operator < ( const VECTOR2D& in_other ) const
		{
			return x < in_other.x && y < in_other.y;
		}

		bool operator <= ( const VECTOR2D& in_other ) const
		{
			return operator<( in_other ) || operator==( in_other );;
		}

		static const VECTOR2D<TYPE> ZERO_VALUE;

		/** VECTOR's X component. */
		TYPE x{};

		/** VECTOR's Y component. */
		TYPE y{};
	};

	template<typename TYPE>
	const VECTOR2D<TYPE> VECTOR2D<TYPE>::ZERO_VALUE = VECTOR2D<TYPE>(TYPE(), TYPE());
}

#include "core/shared/math/vector_types.h"
