#include "graphics/vulkan_instance.hpp"

void VulkanInstance::create() {
	// check for validation layers

	if (Game::enableValidationLayers && !VkInstanceUtil::checkValidationLayerSupport()) {
		throw std::runtime_error("validation layers requested, but not available!");
	}

	// create instance

	vk::ApplicationInfo appInfo("Hello Triangle", VK_MAKE_VERSION(1, 0, 0), "No Engine", VK_MAKE_VERSION(1, 0, 0), VK_API_VERSION_1_0);

	uint32_t validationLayerCount = 0;
	const char* const* enabledLayerNames = nullptr;
	if (Game::enableValidationLayers) {
		validationLayerCount = static_cast<uint32_t>(Game::validationLayers.size());
		enabledLayerNames = Game::validationLayers.data();
	}

	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;

	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	vk::InstanceCreateInfo createInfo({}, &appInfo, validationLayerCount, enabledLayerNames, glfwExtensionCount, glfwExtensions);

	auto extensions = VkInstanceUtil::getRequiredExtensions();
	createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
	createInfo.ppEnabledExtensionNames = extensions.data();

	vk::createInstance(&createInfo, nullptr, &instance);

	// extra, just gets extensions avaliable:

	uint32_t extensionCount = 0;
	vk::enumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

	std::vector<vk::ExtensionProperties> extensions2(extensionCount);

	vk::enumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions2.data());

	std::cout << "available extensions:" << std::endl;

	for (const auto& extension : extensions2) {
		std::cout << "\t" << extension.extensionName << std::endl;
	}
}

VulkanInstance::operator vk::Instance() const {
	return instance;
}

void VulkanInstance::destroy() {
	instance.destroy();
}

void VulkanInstance::destroySurface(vk::SurfaceKHR surface) {
	this->instance.destroySurfaceKHR(surface);
}
