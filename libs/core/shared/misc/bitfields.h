//////////////////////////////////////////////////////////////////////
//! Copyright Alastair Melville
//////////////////////////////////////////////////////////////////////

#pragma once

namespace core
{
	template<typename TYPE>
	inline constexpr bool are_bits_set(TYPE in_value, TYPE in_bitmask) { return (in_value & in_bitmask) == in_bitmask; }

	template<typename TYPE>
	inline constexpr bool are_bits_part_set(TYPE in_value, TYPE in_bitmask) { return (in_value & in_bitmask) != 0; }

	template<typename TYPE>
	inline constexpr bool are_bits_clear(TYPE in_value, TYPE in_bitmask) { return (in_value & in_bitmask) == 0; }

	template<typename TYPE>
	inline constexpr TYPE set_bits(TYPE in_value, TYPE in_bits) { return static_cast<TYPE>(in_value | in_bits); }

	template<typename TYPE>
	inline constexpr void set_bits(TYPE* in_value, TYPE in_bits) { *in_value |= in_bits; }

	template<typename TYPE>
	inline constexpr TYPE clear_bits(TYPE in_value, TYPE in_bits) { return static_cast<TYPE>(in_value & ~in_bits); }

	template<typename TYPE>
	inline constexpr void clear_bits(TYPE* in_value, TYPE in_bits) { (*in_value) = *in_value & ~in_bits; }
}
