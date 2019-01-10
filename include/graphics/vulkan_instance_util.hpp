#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>

#include <vector>

#include "resources.hpp"

namespace VkInstanceUtil {
	bool checkValidationLayerSupport();
	std::vector<const char*> getRequiredExtensions();
}
