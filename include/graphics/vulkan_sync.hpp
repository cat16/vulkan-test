#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>

#include <vector>

#include "resources.hpp"

class Sync {
public:
	void create(vk::Device device);
	void nextFrame();
	void waitForFences();
	void resetFences();
	vk::Semaphore getImageAvailableSemaphore();
	vk::Semaphore getRenderFinishedSemaphore();
	vk::Fence getInFlightFence();
	void destroy();
private:
	size_t currentFrame;
	std::vector<vk::Semaphore> imageAvailableSemaphores;
	std::vector<vk::Semaphore> renderFinishedSemaphores;
	std::vector<vk::Fence> inFlightFences;

	vk::Device device;
};
