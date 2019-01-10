#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>

#include <vector>
#include <algorithm>

#include "swapchain_util.hpp"

class Swapchain {
public:
	void create(vk::Device device, vk::PhysicalDevice physicalDevice, vk::SurfaceKHR surface, GLFWwindow* window);
	void createImageViews();
	void createFramebuffers(vk::RenderPass renderPass);

	operator vk::SwapchainKHR() const;

	vk::Format getImageFormat();
	vk::Extent2D getExtent();
	std::vector<vk::ImageView> getImageViews();
	std::vector<vk::Framebuffer> getFrameBuffers();

	void destroy();
private:
	vk::SwapchainKHR swapChain;
	vk::Format imageFormat;
	vk::Extent2D extent;
	std::vector<vk::Image> swapChainImages;
	std::vector<vk::ImageView> imageViews;
	std::vector<vk::Framebuffer> framebuffers;

	vk::Device device;
};