
#pragma once

//////////////////////////////////////////////////////////////////////
//! Includes
//////////////////////////////////////////////////////////////////////

#include "gui/shared/graphics/RHI/RHI_context_base.h"

#if PLATFORM_WINDOWS
#define VK_USE_PLATFORM_WIN32_KHR
#endif

#pragma warning(push, 0) // Hide warnings which belong to Vulkan
#include <gui/thirdparty/vulkan/vulkan.h>
#pragma warning(pop)
#include "gui/thirdparty/vk_mem_alloc.h"

#include <unordered_map>
#include <vector>

namespace gui
{
	static const VkPolygonMode vulkan_polygon_mode[] =
	{
		VK_POLYGON_MODE_FILL,
		VK_POLYGON_MODE_LINE,
		VK_POLYGON_MODE_MAX_ENUM
	};

	static const VkCullModeFlags vulkan_cull_mode[] =
	{
		VK_CULL_MODE_NONE,
		VK_CULL_MODE_FRONT_BIT,
		VK_CULL_MODE_BACK_BIT,
		VK_CULL_MODE_FLAG_BITS_MAX_ENUM
	};

	static const VkPrimitiveTopology vulkan_primitive_topology[] =
	{
		VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
		VK_PRIMITIVE_TOPOLOGY_LINE_LIST
	};

	static const VkFormat vulkan_format[] =
	{
		// R
		VK_FORMAT_R8_UNORM,
		VK_FORMAT_R16_UINT,
		VK_FORMAT_R16_SFLOAT,
		VK_FORMAT_R32_UINT,
		VK_FORMAT_R32_SFLOAT,
		// RG
		VK_FORMAT_R8G8_UNORM,
		VK_FORMAT_R16G16_SFLOAT,
		VK_FORMAT_R32G32_SFLOAT,
		// RGB
		VK_FORMAT_B10G11R11_UFLOAT_PACK32,
		VK_FORMAT_R32G32B32_SFLOAT,
		// RGBA
		VK_FORMAT_R8G8B8A8_UNORM,
		VK_FORMAT_A2R10G10B10_UNORM_PACK32,
		VK_FORMAT_R16G16B16A16_SNORM,
		VK_FORMAT_R16G16B16A16_SFLOAT,
		VK_FORMAT_R32G32B32A32_SFLOAT,
		// DEPTH
		VK_FORMAT_D32_SFLOAT,
		VK_FORMAT_D32_SFLOAT_S8_UINT,

		VK_FORMAT_MAX_ENUM
	};

	static const VkSamplerAddressMode vulkan_sampler_address_mode[] =
	{
		VK_SAMPLER_ADDRESS_MODE_REPEAT,
		VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT,
		VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE,
		VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER,
		VK_SAMPLER_ADDRESS_MODE_MIRROR_CLAMP_TO_EDGE
	};

	static const VkCompareOp vulkan_compare_operator[] =
	{
		VK_COMPARE_OP_NEVER,
		VK_COMPARE_OP_LESS,
		VK_COMPARE_OP_EQUAL,
		VK_COMPARE_OP_LESS_OR_EQUAL,
		VK_COMPARE_OP_GREATER,
		VK_COMPARE_OP_NOT_EQUAL,
		VK_COMPARE_OP_GREATER_OR_EQUAL,
		VK_COMPARE_OP_ALWAYS
	};

	static const VkStencilOp vulkan_stencil_operation[] =
	{
		VK_STENCIL_OP_KEEP,
		VK_STENCIL_OP_ZERO,
		VK_STENCIL_OP_REPLACE,
		VK_STENCIL_OP_INCREMENT_AND_CLAMP,
		VK_STENCIL_OP_DECREMENT_AND_CLAMP,
		VK_STENCIL_OP_INVERT,
		VK_STENCIL_OP_INCREMENT_AND_WRAP,
		VK_STENCIL_OP_DECREMENT_AND_WRAP
	};

	static const VkBlendFactor vulkan_blend_factor[] =
	{
		VK_BLEND_FACTOR_ZERO,
		VK_BLEND_FACTOR_ONE,
		VK_BLEND_FACTOR_SRC_COLOR,
		VK_BLEND_FACTOR_ONE_MINUS_SRC_COLOR,
		VK_BLEND_FACTOR_SRC_ALPHA,
		VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
		VK_BLEND_FACTOR_DST_ALPHA,
		VK_BLEND_FACTOR_ONE_MINUS_DST_ALPHA,
		VK_BLEND_FACTOR_DST_COLOR,
		VK_BLEND_FACTOR_ONE_MINUS_DST_COLOR,
		VK_BLEND_FACTOR_SRC_ALPHA_SATURATE,
		VK_BLEND_FACTOR_CONSTANT_COLOR,
		VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_COLOR,
		VK_BLEND_FACTOR_SRC1_COLOR,
		VK_BLEND_FACTOR_ONE_MINUS_SRC1_COLOR,
		VK_BLEND_FACTOR_SRC1_ALPHA,
		VK_BLEND_FACTOR_ONE_MINUS_SRC1_ALPHA
	};

	static const VkBlendOp vulkan_blend_operation[] =
	{
		VK_BLEND_OP_ADD,
		VK_BLEND_OP_SUBTRACT,
		VK_BLEND_OP_REVERSE_SUBTRACT,
		VK_BLEND_OP_MIN,
		VK_BLEND_OP_MAX
	};

	static const VkFilter vulkan_filter[] =
	{
		VK_FILTER_NEAREST,
		VK_FILTER_LINEAR
	};

	static const VkSamplerMipmapMode vulkan_mipmap_mode[] =
	{
		VK_SAMPLER_MIPMAP_MODE_NEAREST,
		VK_SAMPLER_MIPMAP_MODE_LINEAR
	};

	static const VkImageLayout vulkan_image_layout[] =
	{
		VK_IMAGE_LAYOUT_UNDEFINED,
		VK_IMAGE_LAYOUT_GENERAL,
		VK_IMAGE_LAYOUT_PREINITIALIZED,
		VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
		VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
		VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL,
		VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
		VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
		VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
	};

	struct RENDERING_CONTEXT_VULKAN : public RENDERING_CONTEXT_BASE
	{
        RHI_Api_Type api_type{ RHI_Api_Type::RHI_Api_Vulkan };
        uint32_t api_version = 0;
        VkInstance instance = nullptr;
        VkPhysicalDevice device_physical = nullptr;
        VkDevice device = nullptr;
        VkPhysicalDeviceProperties device_properties = {};
        VkPhysicalDeviceVulkan12Features device_features_1_2 = { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES };
        VkPhysicalDeviceFeatures2 device_features = { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2, &device_features_1_2 };
        VkFormat surface_format = VK_FORMAT_UNDEFINED;
        VkColorSpaceKHR surface_color_space = VK_COLOR_SPACE_MAX_ENUM_KHR;
        VmaAllocator allocator = nullptr;
        std::unordered_map<uint64_t, VmaAllocation> allocations;

        // Extensions
#ifdef DEBUG
        /*
        https://vulkan.lunarg.com/doc/view/1.2.135.0/mac/validation_layers.html

        VK_LAYER_KHRONOS_validation
        ===================================
        The main, comprehensive Khronos validation layer -- this layer encompasses the entire
        functionality of the layers listed below, and supersedes them. As the other layers
        are deprecated this layer should be used for all validation going forward.

        VK_EXT_debug_utils
        ==================
        Create a debug messenger which will pass along debug messages to an application supplied callback.
        Identify specific Vulkan objects using a name or tag to improve tracking.
        Identify specific sections within a VkQueue or VkCommandBuffer using labels to aid organization and offline analysis in external tools.

        */
        std::vector<const char*> extensions_device = { "VK_KHR_swapchain", "VK_EXT_memory_budget", "VK_EXT_depth_clip_enable", "VK_KHR_timeline_semaphore" };
        std::vector<const char*> validation_layers = { "VK_LAYER_KHRONOS_validation" };
        std::vector<VkValidationFeatureEnableEXT> validation_extensions = { VK_VALIDATION_FEATURE_ENABLE_BEST_PRACTICES_EXT, VK_VALIDATION_FEATURE_ENABLE_SYNCHRONIZATION_VALIDATION_EXT };
        std::vector<const char*> extensions_instance = { "VK_KHR_surface", "VK_KHR_win32_surface", "VK_EXT_debug_report", "VK_EXT_debug_utils" };
#else
        std::vector<const char*> extensions_device = { "VK_KHR_swapchain", "VK_EXT_memory_budget", "VK_EXT_depth_clip_enable", "VK_KHR_timeline_semaphore" };
        std::vector<const char*> validation_layers = { };
        std::vector<VkValidationFeatureEnableEXT> validation_extensions = { };
        std::vector<const char*> extensions_instance = { "VK_KHR_surface", "VK_KHR_win32_surface" };
#endif

        bool initalise_allocator();
        void destroy_allocator();

		// Queues
		void* queue_graphics = nullptr;
		void* queue_compute = nullptr;
		void* queue_transfer = nullptr;
		uint32_t queue_graphics_index = 0;
		uint32_t queue_transfer_index = 0;
		uint32_t queue_compute_index = 0;
	};
}
