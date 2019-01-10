#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>

#include <set>

#include "../resources.hpp"
#include "device_util.hpp"
#include "swapchain_util.hpp"

class Device {
public:
	void create(vk::Instance instance, vk::SurfaceKHR surface, std::vector<const char*> validationLayers);
	operator vk::Device() const;
	vk::PhysicalDevice getPhysical();
	vk::Queue getGraphicsQueue();
	vk::Queue getPresentQueue();
	void acquireNextImage(vk::SwapchainKHR surface, uint64_t timeout, vk::Semaphore semaphore, uint32_t* imageIndex);
	void waitIdle();
	void destroy();
private:
	vk::Device logicalDevice;
	vk::PhysicalDevice physicalDevice;
	vk::Queue graphicsQueue;
	vk::Queue presentQueue;
};