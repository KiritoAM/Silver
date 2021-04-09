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

namespace gui
{
	class CAMERA3D
	{
	public:
		float m_near_plane{ 0.3f };
		float m_far_plane{ 1000.0f };
		core::FVECTOR3D m_position;
		core::QUATERNION m_rotation;

	private:
		core::MATRIX m_view;
		core::MATRIX m_projection;
		core::MATRIX m_view_projection;
	};
}
