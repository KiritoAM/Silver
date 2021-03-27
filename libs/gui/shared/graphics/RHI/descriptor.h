
#pragma once

//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "gui/shared/graphics/RHI/RHI_types.h"

#include <string>

namespace gui
{
	struct DESCRIPTOR
	{
		uint32_t slot = 0;
		uint32_t stage = 0;
		uint64_t offset = 0;
		uint64_t range = 0;
		RHI_Descriptor_Type type = RHI_Descriptor_Type::Undefined;
		RHI_Image_Layout layout = RHI_Image_Layout::Undefined;
		bool is_storage = false;
		bool is_dynamic_constant_buffer = false;
		std::string name = "";
		void* resource = nullptr;
	};
}
