#include "graphics/vulkan_debug.hpp"

void VulkanDebug::bound(vk::Instance instance) {
	this->instance = instance;
}

static VKAPI_ATTR vk::Bool32 VKAPI_CALL debugCallback(
	VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT messageType,
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

	instance.createDebugUtilsMessengerEXT(&createInfo, nullptr, &callback);
}

void VulkanDebug::destroyDebugCallback() {
	if (Game::enableValidationLayers) {
		DestroyDebugUtilsMessengerEXT(nullptr);
	}
}
