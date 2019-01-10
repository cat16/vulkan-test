#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>

#include <glm.hpp>

#include <array>

#include "../util.hpp"

class ShaderModule {
public:
	void create(vk::Device device, const std::string& filename, vk::ShaderStageFlagBits stage);
	vk::PipelineShaderStageCreateInfo getStageCreateInfo();
	void destroy();
private:
	vk::ShaderModule module;
	vk::PipelineShaderStageCreateInfo stageCreateInfo;

	vk::Device device;
};