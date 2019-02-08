#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>

#include "shader.hpp"
#include "buffer/vertex.hpp"

class GraphicsPipeline {
public:
	void create(vk::Device device, vk::Extent2D swapChainExtent, vk::RenderPass renderPass);
	operator vk::Pipeline() const;
	void destroy();
private:
	vk::Pipeline pipeline;

	vk::Device device;
	vk::PipelineLayout layout;
};