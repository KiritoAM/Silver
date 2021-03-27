//////////////////////////////////////////////////////////////////////
//! Copyright Alastair Melville
//////////////////////////////////////////////////////////////////////

#pragma once

namespace core
{
	template<typename TYPE>
	struct VECTOR4D
	{
		TYPE X{};

		TYPE Y{};

		TYPE Z{};

		TYPE A{};

		VECTOR4D() = default;

		explicit VECTOR4D(TYPE InXYZ)
			: X(InXYZ)
			, Y(InXYZ)
			, Z(InXYZ)
		{}

		VECTOR4D(TYPE InX, TYPE InY, TYPE InZ, TYPE InA)
			: X(InX)
			, Y(InY)
			, Z(InZ)
			, A(InA)
		{}

		static const VECTOR4D<TYPE> ZERO_VALUE;

		bool is_valid() const;

		/**
		 * Check against another VECTOR4D for equality.
		 *
		 * @param V The VECTOR4D to check against.
		 * @return true if the VECTOR4Ds are equal, false otherwise.
		 */
		bool operator==(const VECTOR4D<TYPE>& InVECTOR4D) const;

		bool operator!=(const VECTOR4D<TYPE>& InVECTOR4D) const;

		template<typename TYPE>
		void operator=(const VECTOR4D<TYPE>& InVECTOR4D)
		{
			X = InVECTOR4D.X;
			Y = InVECTOR4D.Y;
			Z = InVECTOR4D.Z;
			A = InVECTOR4D.A;
		}

		/**
		 * Adds another VECTOR4D to this.
		 * Uses component-wise addition.
		 *
		 * @param V VECTOR4D to add to this.
		 * @return Copy of the VECTOR4D after addition.
		 */
		VECTOR4D<TYPE> operator+=(const VECTOR4D<TYPE>& InVECTOR4D);

		/**
		 * Subtracts another VECTOR4D from this.
		 * Uses component-wise subtraction.
		 *
		 * @param V VECTOR4D to subtract from this.
		 * @return Copy of the VECTOR4D after subtraction.
		 */
		VECTOR4D<TYPE> operator-=(const VECTOR4D<TYPE>& InVECTOR4D);
	};

	template<typename TYPE>
	const VECTOR4D<TYPE> VECTOR4D<TYPE>::ZERO_VALUE = VECTOR4D<TYPE>();

	template<typename TYPE>
	inline bool VECTOR4D<TYPE>::is_valid() const
	{
		return *this != ZERO_VALUE;
	}

	template<typename TYPE>
	inline bool VECTOR4D<TYPE>::operator==(const VECTOR4D<TYPE>& InVECTOR4D) const
	{
		return X == InVECTOR4D.X && Y == InVECTOR4D.Y && Z == InVECTOR4D.Z && A == InVECTOR4D.A;
	}

	template<typename TYPE>
	inline bool VECTOR4D<TYPE>::operator!=(const VECTOR4D<TYPE>& InVECTOR4D) const
	{
		return !operator==(InVECTOR4D);
	}

	template<typename TYPE>
	inline VECTOR4D<TYPE> VECTOR4D<TYPE>::operator+=(const VECTOR4D<TYPE>& InVECTOR4D)
	{
		X += InVECTOR4D.X;
		Y += InVECTOR4D.Y;
		Z += InVECTOR4D.Z;
		A += InVECTOR4D.A;
		return *this;
	}

	template<typename TYPE>
	inline VECTOR4D<TYPE> VECTOR4D<TYPE>::operator-=(const VECTOR4D<TYPE>& InVECTOR4D)
	{
		X -= InVECTOR4D.X;
		Y -= InVECTOR4D.Y;
		Z -= InVECTOR4D.Z;
		A -= InVECTOR4D.A;
		return *this;
	}


	using FVECTOR4D = VECTOR4D<float>;
}
