#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>
#include <glm.hpp>

#include <vector>

#include "swapchain_util.hpp"

class CommandPool {
public:
	void create(vk::PhysicalDevice physicalDevice, vk::SurfaceKHR surface, vk::Device device);
	void createBuffers(std::vector<vk::Framebuffer> frameBuffers, vk::RenderPass renderPass, vk::Extent2D extent, vk::Pipeline pipeline, vk::Buffer vertexBuffer, size_t verticesSize);
	operator vk::CommandPool() const;
	std::vector<vk::CommandBuffer> getBuffers();
	void destory();
	void freeBuffers();
private:
	vk::CommandPool commandPool;
	std::vector<vk::CommandBuffer> commandBuffers;

	vk::Device device;
};
