//////////////////////////////////////////////////////////////////////
//! Copyright Alastair Melville
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "core/shared/math/math_utilities.h"
#include "core/shared/math/transform.h"

namespace core
{
	void TRANSFORM::set_position( const core::FVECTOR3D& position )
	{
		m_matrix = { position, m_matrix.GetRotation(), m_matrix.GetScale()};
	}

	void TRANSFORM::set_rotation( const core::QUATERNION& rotation )
	{
		m_matrix = { m_matrix.GetTranslation(), rotation, m_matrix.GetScale() };
	}

	void TRANSFORM::set_scale( core::FVECTOR3D scale )
	{
		scale.x = (scale.x == 0.0f) ? core::EPSILON : scale.x;
		scale.y = (scale.y == 0.0f) ? core::EPSILON : scale.y;
		scale.z = (scale.z == 0.0f) ? core::EPSILON : scale.z;

		m_matrix = { m_matrix.GetTranslation(), m_matrix.GetRotation(), scale };
	}
}
