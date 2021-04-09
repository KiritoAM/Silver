//////////////////////////////////////////////////////////////////////
//! Copyright Alastair Melville
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "input/shared/mouse/mouse.h"

#include "input/shared/input_types.h"
#include "input/shared/mouse/mouse_codes.h"

namespace input
{
	struct INPUT_CONTAINER
	{
		EINPUT_TYPE m_input_type{ EINPUT_TYPE::INVALID };
		BUTTON m_button{ BUTTON::INVALID };
		float m_input_value{ 0.0f };
	};

	void determine_input_types(const core::FVECTOR2D& in_position_delta, std::vector<INPUT_CONTAINER>& out_input_containers)
	{
		if (in_position_delta.x != 0)
		{
			out_input_containers.push_back({ EINPUT_TYPE::MOUSE_MOVEMENT_HORIZONTAL, BUTTON::INVALID, in_position_delta.x });
		}

		if (in_position_delta.y != 0)
		{
			out_input_containers.push_back({ EINPUT_TYPE::MOUSE_MOVEMENT_VERTICAL, BUTTON::INVALID, in_position_delta.y });
		}
	}
}

namespace input
{
	void MOUSE_DEVICE::on_mouse_moved()
	{
		super::on_mouse_moved();

		std::vector<INPUT_CONTAINER> input_containers;
		determine_input_types(m_pos_delta_norm, input_containers);

		m_pointing_device_delegate.m_inner.execute<void, MOUSE_DEVICE*>(this);

		m_on_moved_delegate.m_inner.execute<const MOUSE_POS_TYPE&, const MOUSE_POS_TYPE&>(m_current_position, m_pos_delta);

		/*{
			auto& input_manager_delegate = input::INPUT_MANAGER::get_singleton().get_input_manager_delegate();

			for (INPUT_CONTAINER& input_container : input_containers)
			{
				input_manager_delegate.m_inner.execute<void, input::INPUT_BINDING_WRAPPER, float>(new AXIS_INPUT_BINDING(input_container.m_input_type, input_container.m_button),
					std::move(input_container.m_input_value));
			}
		}*/
	}
}

