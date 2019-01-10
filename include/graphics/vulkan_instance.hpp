#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>

#include <vector>
#include <iostream>

#include "resources.hpp"
#include "vulkan_instance_util.hpp"

class VulkanInstance {
public:
	void create();
	operator vk::Instance() const;
	void destroy();
	void destroySurface(vk::SurfaceKHR surface);
private:
	vk::Instance instance;
};