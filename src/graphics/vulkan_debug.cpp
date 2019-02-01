#include "graphics/vulkan_debug.hpp"

void VulkanDebug::bound(vk::Instance instance, vk::DispatchLoaderDynamic dldy) {
	this->instance = instance;
	this->dldy = dldy;
}

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
	VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
	VkDebugUtilsMessageSeverityFlagsEXT messageType,
	const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
	void* pUserData) {

	std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

	return VK_FALSE;
}

void VulkanDebug::setupDebugCallback() {
	if (!Game::enableValidationLayers) return;
	vk::DebugUtilsMessengerCreateInfoEXT createInfo(
		{},
		vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose | vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning | vk::DebugUtilsMessageSeverityFlagBitsEXT::eError,
		vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral | vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation | vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance,
		debugCallback,
		nullptr);

	instance.createDebugUtilsMessengerEXT(&createInfo, nullptr, &callback, dldy);
}

void VulkanDebug::destroyDebugCallback() {
	if (Game::enableValidationLayers) {
		DestroyDebugUtilsMessengerEXT(nullptr);
	}
}

void VulkanDebug::DestroyDebugUtilsMessengerEXT(const vk::AllocationCallbacks* pAllocator) {
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) instance.getProcAddr("vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr) {
		instance.destroyDebugUtilsMessengerEXT(callback, pAllocator, dldy);
    }
}
