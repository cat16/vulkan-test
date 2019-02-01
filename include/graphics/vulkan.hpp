#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>

#include "resources.hpp"
#include "graphics/vulkan_instance.hpp"
#include "graphics/device.hpp"
#include "graphics/graphics_pipeline.hpp"
#include "graphics/renderpass.hpp"
#include "graphics/swapchain.hpp"
#include "graphics/command_pool.hpp"
#include "graphics/vertex.hpp"
#include "graphics/vulkan_debug.hpp"
#include "graphics/vulkan_sync.hpp"

class Vulkan {
public:
	void init(GLFWwindow * window);
	Sync getSync();
	void cleanup();
	void drawFrame(bool frameBufferResized);
	void recreateSwapChain();
	void waitForDeviceIdle();
private:
	vk::DispatchLoaderDynamic dldy;
	VulkanDebug debug;

	GLFWwindow * window;
	VulkanInstance instance;
	Device device;
	vk::SurfaceKHR surface;
	Sync sync;

	Swapchain swapChain;
	RenderPass renderPass;
	GraphicsPipeline graphicsPipeline;
	CommandPool commandPool;
	VertexBuffer vertexBuffer;

	void createSurface(GLFWwindow * window);

	void initSwapChain();
	void cleanupSwapChain();
};