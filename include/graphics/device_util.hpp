#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>

#include <set>

#include "swapchain_util.hpp"

#pragma once

namespace DeviceUtil {
	vk::PhysicalDevice pickPhysicalDevice(vk::Instance instance, vk::SurfaceKHR surface, std::vector<const char*> extensions);
	bool isDeviceSuitable(vk::PhysicalDevice device, vk::SurfaceKHR surface, std::vector<const char*> extensions);
	bool checkDeviceExtensionSupport(vk::PhysicalDevice device, std::vector<const char*> extensions);
}