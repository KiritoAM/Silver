//////////////////////////////////////////////////////////////////////
//! Copyright Alastair Melville
//////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "core/shared/math/vector3d.h"

namespace core
{
	template<typename TYPE>
	struct ROTATOR : public core::VECTOR3D<TYPE>
	{
		using super = core::VECTOR3D<TYPE>;
		using super::X;
		using super::Y;
		using super::Z;

	public:
		ROTATOR()
			: super()
		{}

		explicit ROTATOR(TYPE in_value)
			: super(in_value)
		{}

		ROTATOR(TYPE in_pitch, TYPE in_yaw, TYPE in_roll)
			: super(in_pitch, in_yaw, in_roll)
		{}

		ROTATOR<TYPE> operator+(const ROTATOR<TYPE>& in_rotator) const;

		ROTATOR<TYPE>& operator+=(const ROTATOR<TYPE>& InVector);

		TYPE get_pitch() const { return X; }
		TYPE get_yaw() const { return Y; }
		TYPE get_roll() const { return Z; }

		ROTATOR<TYPE>& add_pitch(TYPE in_value) { X += in_value; return *this; }
		ROTATOR<TYPE>& add_yaw(TYPE in_value) { Y += in_value; return *this; }
	};

	template<typename TYPE>
	inline ROTATOR<TYPE> ROTATOR<TYPE>::operator+(const ROTATOR<TYPE>& in_rotator) const
	{
		VECTOR3D<TYPE> as_super = super::operator + (in_rotator);
		return *static_cast< ROTATOR<TYPE>* >( &as_super );
	}

	template<typename TYPE>
	inline ROTATOR<TYPE>& ROTATOR<TYPE>::operator+=(const ROTATOR<TYPE>& in_rotator)
	{
		super::operator+=(in_rotator);
		return *this;
	}

	using FROTATOR = ROTATOR<float>;
}
