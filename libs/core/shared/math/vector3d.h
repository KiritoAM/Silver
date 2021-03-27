//////////////////////////////////////////////////////////////////////
//! Copyright Alastair Melville
//////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include <math.h>

namespace core
{
	/**
	 * A vector in 3-D space composed of components (X, Y, Z) with TYPEing point precision.
	 */
	template<typename TYPE>
	struct VECTOR3D
	{
	public:
		VECTOR3D()
		{}

		constexpr explicit VECTOR3D(TYPE InXYZ)
			: X(InXYZ)
			, Y(InXYZ)
			, Z(InXYZ)
		{}

		constexpr VECTOR3D(TYPE InX, TYPE InY, TYPE InZ)
			: X(InX)
			, Y(InY)
			, Z(InZ)
		{}

		bool operator==(const VECTOR3D<TYPE>& in_vector) const;

		VECTOR3D<TYPE> operator+(const VECTOR3D<TYPE>& in_vector) const;

		VECTOR3D<TYPE> operator+(float in_scalar) const;

		VECTOR3D<TYPE> operator-(const VECTOR3D<TYPE>& in_vector) const;

		VECTOR3D<TYPE> operator-() const;

		VECTOR3D<TYPE>& operator+=(const VECTOR3D<TYPE>& in_vector);

		VECTOR3D<TYPE>& operator-=(const VECTOR3D<TYPE>& in_vector);

		VECTOR3D<TYPE> operator*(float in_scale) const;

		VECTOR3D<TYPE> operator^(const VECTOR3D<TYPE>& in_vector) const;

		float get_size() const;

		TYPE X{};

		TYPE Y{};

		TYPE Z{};
	};

	template<typename TYPE>
	inline bool VECTOR3D<TYPE>::operator==(const VECTOR3D<TYPE>& in_vector) const
	{
		return X == in_vector.X && Y == in_vector.Y && Z == in_vector.Z;
	}

	template<typename TYPE>
	inline VECTOR3D<TYPE> VECTOR3D<TYPE>::operator+(const VECTOR3D<TYPE>& in_vector) const
	{
		return { X + in_vector.X, Y + in_vector.Y, Z + in_vector.Z };
	}

	template<typename TYPE>
	inline VECTOR3D<TYPE> VECTOR3D<TYPE>::operator+(float in_scalar) const
	{
		return { X + in_scalar, Y + in_scalar, Z + in_scalar };
	}

	template<typename TYPE>
	inline VECTOR3D<TYPE> VECTOR3D<TYPE>::operator-(const VECTOR3D<TYPE>& in_vector) const
	{
		return { X - in_vector.X, Y - in_vector.Y, Z - in_vector.Z };
	}

	template<typename TYPE>
	inline VECTOR3D<TYPE> VECTOR3D<TYPE>::operator-() const
	{
		return { -X, -Y, -Z };
	}

	template<typename TYPE>
	inline VECTOR3D<TYPE>& VECTOR3D<TYPE>::operator+=(const VECTOR3D<TYPE>& in_vector)
	{
		X += in_vector.X;
		Y += in_vector.Y;
		Z += in_vector.Z;
		return *this;
	}

	template<typename TYPE>
	inline VECTOR3D<TYPE>& VECTOR3D<TYPE>::operator-=(const VECTOR3D<TYPE>& in_vector)
	{
		X -= in_vector.X;
		Y -= in_vector.Y;
		Z -= in_vector.Z;
		return *this;
	}

	template<typename TYPE>
	inline VECTOR3D<TYPE> VECTOR3D<TYPE>::operator*(float in_scale) const
	{
		return { X * in_scale, Y * in_scale, Z * in_scale };
	}

	template<typename TYPE>
	inline VECTOR3D<TYPE> VECTOR3D<TYPE>::operator^(const VECTOR3D<TYPE>& in_vector) const
	{
		return { Y * in_vector.Z - Z * in_vector.Y,
			Z * in_vector.X - X * in_vector.Z,
			X * in_vector.Y - Y * in_vector.X };
	}

	template<typename TYPE>
	inline float VECTOR3D<TYPE>::get_size() const
	{
		return sqrtf(X*X + Y*Y + Z*Z);
	}

	//////////////////////////////////////////////////////////////////////
	//! Types
	//////////////////////////////////////////////////////////////////////

	using FVECTOR = VECTOR3D<float>;

	//////////////////////////////////////////////////////////////////////
	//! Constants
	//////////////////////////////////////////////////////////////////////

	static inline constexpr FVECTOR ZERO_VALUE(0.0f);

	static inline constexpr FVECTOR ONE_VECTOR(1.0f);

	static inline constexpr FVECTOR UP_VECTOR(0.0f, 0.0f, 1.0f);

	static inline constexpr FVECTOR DOWN_VECTOR(0.0f, 0.0f, -1.0f);

	static inline constexpr FVECTOR FORWARD_VECTOR(1.0f, 0.0f, 0.0f);

	static inline constexpr FVECTOR BACKWARD_VECTOR(-1.0f, 0.0f, 0.0f);

	static inline constexpr FVECTOR RIGHT_VECTOR(0.0f, 1.0f, 0.0f);

	static inline constexpr FVECTOR LEFT_VECTOR(0.0f, -1.0f, 0.0f);
}
