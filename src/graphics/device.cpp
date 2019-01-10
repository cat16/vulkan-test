#include "graphics\device.hpp"

void Device::create(vk::Instance instance, vk::SurfaceKHR surface, std::vector<const char*> validationLayers) {
	physicalDevice = DeviceUtil::pickPhysicalDevice(instance, surface, Game::deviceExtensions);
	SwapchainUtil::QueueFamilyIndices indices = SwapchainUtil::findQueueFamilies(physicalDevice, surface);

	std::vector<vk::DeviceQueueCreateInfo> queueCreateInfos;
	std::set<int> uniqueQueueFamilies = { indices.graphicsFamily, indices.presentFamily };

	float queuePriority = 1.0f;
	for (int queueFamily : uniqueQueueFamilies) {
		vk::DeviceQueueCreateInfo queueCreateInfo({}, queueFamily, 1, &queuePriority);
		queueCreateInfos.push_back(queueCreateInfo);
	}

	vk::PhysicalDeviceFeatures deviceFeatures = {};

	vk::DeviceCreateInfo createInfo(
	{},
		static_cast<uint32_t>(queueCreateInfos.size()),
		queueCreateInfos.data(),
		Game::enableValidationLayers ? static_cast<uint32_t>(validationLayers.size()) : 0,
		Game::enableValidationLayers ? validationLayers.data() : NULL,
		static_cast<uint32_t>(Game::deviceExtensions.size()),
		Game::deviceExtensions.data()
	);

	physicalDevice.createDevice(&createInfo, nullptr, &logicalDevice);

	logicalDevice.getQueue(indices.graphicsFamily, 0, &graphicsQueue);
	logicalDevice.getQueue(indices.presentFamily, 0, &presentQueue);
}

Device::operator vk::Device() const {
	return logicalDevice;
}

vk::PhysicalDevice Device::getPhysical() {
	return physicalDevice;
}

vk::Queue Device::getGraphicsQueue() {
	return graphicsQueue;
}

vk::Queue Device::getPresentQueue() {
	return presentQueue;
}

void Device::acquireNextImage(vk::SwapchainKHR surface, uint64_t timeout, vk::Semaphore semaphore, uint32_t* imageIndex) {
	this->logicalDevice.acquireNextImageKHR(surface, timeout, semaphore, nullptr, imageIndex);
}

void Device::waitIdle() {
	logicalDevice.waitIdle();
}

void Device::destroy() {
	logicalDevice.destroy();
}