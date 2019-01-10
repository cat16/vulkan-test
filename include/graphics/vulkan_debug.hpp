#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>

#include <iostream>

#include "resources.hpp"

class VulkanDebug {
public:
	void bound(vk::Instance instance);
	void setupDebugCallback();
	void destroyDebugCallback();
private:
	vk::Instance instance;
	vk::DebugUtilsMessengerEXT callback;

	void createDebugUtilsMessengerEXT(const vk::DebugUtilsMessengerCreateInfoEXT* pCreateInfo, const vk::AllocationCallbacks* pAllocator);
	void DestroyDebugUtilsMessengerEXT(const vk::AllocationCallbacks* pAllocator);
};
