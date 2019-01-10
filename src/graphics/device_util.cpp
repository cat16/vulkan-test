#include "graphics/device_util.hpp"

vk::PhysicalDevice DeviceUtil::pickPhysicalDevice(vk::Instance instance, vk::SurfaceKHR surface, std::vector<const char*> extensions) {
	uint32_t deviceCount = 0;
	instance.enumeratePhysicalDevices(&deviceCount, nullptr);
	if (deviceCount == 0) {
		throw std::runtime_error("failed to find GPUs with Vulkan support!");
	}
	std::vector<vk::PhysicalDevice> devices(deviceCount);
	instance.enumeratePhysicalDevices(&deviceCount, devices.data());

	vk::PhysicalDevice physicalDevice = nullptr;

	for (const auto& device : devices) {
		if (isDeviceSuitable(device, surface, extensions)) {
			physicalDevice = device;
			break;
		}
	}

	if (physicalDevice) {
		throw std::runtime_error("failed to find a suitable GPU!");
	}

	return physicalDevice;
}

bool DeviceUtil::isDeviceSuitable(vk::PhysicalDevice device, vk::SurfaceKHR surface, std::vector<const char*> extensions) {
	SwapchainUtil::QueueFamilyIndices indices = SwapchainUtil::findQueueFamilies(device, surface);

	bool extensionsSupported = checkDeviceExtensionSupport(device, extensions);

	bool swapChainAdequate = false;
	if (extensionsSupported) {
		SwapchainUtil::SwapChainSupportDetails swapChainSupport = SwapchainUtil::querySwapChainSupport(device, surface);
		swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
	}

	return indices.isComplete() && extensionsSupported && swapChainAdequate;
}

bool DeviceUtil::checkDeviceExtensionSupport(vk::PhysicalDevice device, std::vector<const char*> extensions) {
	uint32_t extensionCount;
	device.enumerateDeviceExtensionProperties(nullptr, &extensionCount, nullptr);

	std::vector<vk::ExtensionProperties> availableExtensions(extensionCount);
	device.enumerateDeviceExtensionProperties(nullptr, &extensionCount, availableExtensions.data());

	std::set<std::string> requiredExtensions(extensions.begin(), extensions.end());

	for (const auto& extension : availableExtensions) {
		requiredExtensions.erase(extension.extensionName);
	}

	return requiredExtensions.empty();
}