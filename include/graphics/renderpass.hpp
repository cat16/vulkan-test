#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>

#include <stdexcept>

class RenderPass {
public:
	void create(vk::Device device, vk::Format swapChainImageFormat);
	operator vk::RenderPass() const;
	void destroy();
private:
	vk::RenderPass renderPass;

	vk::Device device;
};