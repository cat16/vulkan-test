#include "graphics/swapchain.hpp"

void Swapchain::create(vk::Device device, vk::PhysicalDevice physicalDevice, vk::SurfaceKHR surface, GLFWwindow* window) {
	SwapchainUtil::SwapChainSupportDetails swapChainSupport = SwapchainUtil::querySwapChainSupport(physicalDevice, surface);

	vk::SurfaceFormatKHR surfaceFormat = SwapchainUtil::chooseSwapSurfaceFormat(swapChainSupport.formats);
	vk::PresentModeKHR presentMode = SwapchainUtil::chooseSwapPresentMode(swapChainSupport.presentModes);
	vk::Extent2D extent = SwapchainUtil::chooseSwapExtent(swapChainSupport.capabilities, window);

	uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
	if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
		imageCount = swapChainSupport.capabilities.maxImageCount;
	}

	SwapchainUtil::QueueFamilyIndices indices = SwapchainUtil::findQueueFamilies(physicalDevice, surface);

	vk::SharingMode imageSharingMode;
	int queueFamilyIndexCount;
	uint32_t* queueFamilyIndices;

	if (indices.graphicsFamily != indices.presentFamily) {
		imageSharingMode = vk::SharingMode::eConcurrent;
		queueFamilyIndexCount = 2;
		queueFamilyIndices = new uint32_t[2]{(uint32_t)indices.graphicsFamily, (uint32_t)indices.presentFamily};
	} else {
		imageSharingMode = vk::SharingMode::eExclusive;
		queueFamilyIndexCount = 0; // Optional
		queueFamilyIndices = nullptr; // Optional
	}

	vk::SwapchainCreateInfoKHR createInfo(
	{}, surface, imageCount,
		surfaceFormat.format, surfaceFormat.colorSpace,
		extent, 1, vk::ImageUsageFlagBits::eColorAttachment, imageSharingMode,
		queueFamilyIndexCount, queueFamilyIndices, swapChainSupport.capabilities.currentTransform,
		vk::CompositeAlphaFlagBitsKHR::eOpaque, presentMode, VK_TRUE
	);

	device.createSwapchainKHR(&createInfo, nullptr, &swapChain);

	device.getSwapchainImagesKHR(swapChain, &imageCount, nullptr);
	swapChainImages.resize(imageCount);
	device.getSwapchainImagesKHR(swapChain, &imageCount, swapChainImages.data());

	this->imageFormat = surfaceFormat.format;
	this->extent = extent;

	this->device = device;
}

void Swapchain::createImageViews() {
	imageViews.resize(swapChainImages.size());
	for (size_t i = 0; i < swapChainImages.size(); i++) {
		vk::ImageViewCreateInfo createInfo(
		{}, swapChainImages[i], vk::ImageViewType::e2D, imageFormat,
			vk::ComponentMapping(
				vk::ComponentSwizzle::eIdentity,
				vk::ComponentSwizzle::eIdentity,
				vk::ComponentSwizzle::eIdentity,
				vk::ComponentSwizzle::eIdentity
			),
			vk::ImageSubresourceRange(
		{vk::ImageAspectFlagBits::eColor},
				0,
				1,
				0,
				1
			)
		);

		device.createImageView(&createInfo, nullptr, &imageViews[i]);
	}
}

void Swapchain::createFramebuffers(vk::RenderPass renderPass) {
	framebuffers.resize(imageViews.size());

	for (size_t i = 0; i < imageViews.size(); i++) {
		vk::ImageView attachments[] = {
			imageViews[i]
		};

		vk::FramebufferCreateInfo framebufferInfo({}, renderPass, 1, attachments, extent.width, extent.height, 1);

		device.createFramebuffer(&framebufferInfo, nullptr, &framebuffers[i]);
	}
}

Swapchain::operator vk::SwapchainKHR() const {
	return swapChain;
}

vk::Format Swapchain::getImageFormat() {
	return imageFormat;
}

vk::Extent2D Swapchain::getExtent() {
	return extent;
}

std::vector<vk::ImageView> Swapchain::getImageViews() {
	return imageViews;
}

std::vector<vk::Framebuffer> Swapchain::getFrameBuffers() {
	return framebuffers;
}

void Swapchain::destroy() {
	for (size_t i = 0; i < framebuffers.size(); i++) {
		device.destroyFramebuffer(framebuffers[i], nullptr);
	}

	for (size_t i = 0; i < imageViews.size(); i++) {
		device.destroyImageView(imageViews[i], nullptr);
	}

	device.destroySwapchainKHR(swapChain, nullptr);
}
