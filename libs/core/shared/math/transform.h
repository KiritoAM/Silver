//////////////////////////////////////////////////////////////////////
//! Copyright Alastair Melville
//////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "core/shared/math/matrix.h"
#include "core/shared/math/quaternion.h"
#include "core/shared/math/vector3d.h"

namespace core
{
	class TRANSFORM
	{
	public:
		void set_position( const core::FVECTOR3D& position );
		void set_rotation( const core::QUATERNION& rotation );
		void set_scale( core::FVECTOR3D scale );

		const core::MATRIX& get_matrix() const { return m_matrix; }
		core::FVECTOR3D get_position() const { return m_matrix.GetTranslation(); }
		core::QUATERNION get_rotation() const { return m_matrix.GetRotation(); }
		core::FVECTOR3D get_scale() const { return m_matrix.GetScale(); }

	private:
		core::MATRIX m_matrix;
	};
}
