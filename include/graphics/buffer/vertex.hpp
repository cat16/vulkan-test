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

struct Vertex {
	glm::vec2 pos;
	glm::vec3 color;

	static vk::VertexInputBindingDescription getBindingDescription();
	static std::array<vk::VertexInputAttributeDescription, 2> getAttributeDescriptions();
};

class VertexBuffer {
public:
	void create(vk::Device device, vk::CommandPool commandPool, vk::Queue graphicsQueue, vk::PhysicalDevice physicalDevice, std::vector<Vertex> vertices);
	operator vk::Buffer() const;
	size_t getVerticesSize();
	void destroy();
private:
	vk::Buffer buffer;
	vk::DeviceMemory bufferMemory;

	size_t verticesSize;

	vk::Device device;
};