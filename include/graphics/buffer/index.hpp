#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>
#include <glm.hpp>

#include <array>
#include <vector>
#include <stdexcept>

#include "util.hpp"
#include "buffer_util.hpp"

class IndexBuffer {
public:
	void create(vk::Device device, vk::CommandPool commandPool, vk::Queue graphicsQueue, vk::PhysicalDevice physicalDevice, std::vector<uint16_t> indices);
	operator vk::Buffer() const;
	size_t getIndicesSize();
	void destroy();
private:
	vk::Buffer buffer;
	vk::DeviceMemory bufferMemory;

	size_t indicesSize;

	vk::Device device;
};
