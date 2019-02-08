#include "graphics/vulkan.hpp"

void Vulkan::init(GLFWwindow * window) {
	instance.create();
	createSurface(window);

	device.create(instance, surface, Game::validationLayers);
	dldy.init(instance, device);

	debug.bound(instance, dldy);
	debug.setupDebugCallback();

	initSwapChain();
	commandPool.create(device.getPhysical(), surface, device);
	vertexBuffer.create(device, commandPool, device.getGraphicsQueue(), device.getPhysical(), Game::vertices);
	indexBuffer.create(device, commandPool, device.getGraphicsQueue(), device.getPhysical(), Game::indices);
	createCommandPoolBuffers();
	sync.create(device);

	this->window = window;
}

Sync Vulkan::getSync() {
	return sync;
}

void Vulkan::cleanup() {
	cleanupSwapChain();

	vertexBuffer.destroy();
	indexBuffer.destroy();
	sync.destroy();
	commandPool.destory();
	device.destroy();

	debug.destroyDebugCallback();

	instance.destroySurface(surface);
	instance.destroy();
}

void Vulkan::drawFrame(bool framebufferResized) {
	sync.waitForFences();

	uint32_t imageIndex;
	device.acquireNextImage(swapChain, std::numeric_limits<uint64_t>::max(), sync.getImageAvailableSemaphore(), &imageIndex);

	vk::Semaphore waitSemaphores[] = { sync.getImageAvailableSemaphore() };
	vk::PipelineStageFlags waitStages[] = { vk::PipelineStageFlagBits::eColorAttachmentOutput };
	auto commandBuffer = commandPool.getBuffers()[imageIndex];
	vk::Semaphore signalSemaphores[] = { sync.getRenderFinishedSemaphore() };

	vk::SubmitInfo submitInfo(1, waitSemaphores, waitStages, 1, &commandBuffer, 1, signalSemaphores);

	sync.resetFences();

	device.getGraphicsQueue().submit(1, &submitInfo, sync.getInFlightFence());

	vk::SwapchainKHR swapChains[] = { swapChain };

	vk::PresentInfoKHR presentInfo(1, signalSemaphores, 1, swapChains, &imageIndex);

	vk::Result result = device.getPresentQueue().presentKHR(&presentInfo);

	if (result == vk::Result::eErrorOutOfDateKHR || result == vk::Result::eSuboptimalKHR || framebufferResized) {
		framebufferResized = false;
		recreateSwapChain();
	}
	else if (result != vk::Result::eSuccess) {
		throw std::runtime_error("failed to present swap chain image!");
	}

	sync.nextFrame();
}

void Vulkan::createSurface(GLFWwindow * window) {
	VkSurfaceKHR vkSurface;
	if (glfwCreateWindowSurface(VkInstance((vk::Instance)instance), window, nullptr, &vkSurface) != VK_SUCCESS) {
		throw std::runtime_error("failed to create window surface!");
	}
	surface = vk::SurfaceKHR(vkSurface);
}

void Vulkan::initSwapChain() {
	swapChain.create(device, device.getPhysical(), surface, window);
	swapChain.createImageViews();
	renderPass.create(device, swapChain.getImageFormat());
	graphicsPipeline.create(device, swapChain.getExtent(), renderPass);
	swapChain.createFramebuffers(renderPass);
}

void Vulkan::cleanupSwapChain() {
	swapChain.destroy();
	commandPool.freeBuffers();
	graphicsPipeline.destroy();
	renderPass.destroy();
}

void Vulkan::recreateSwapChain() {
	device.waitIdle();

	cleanupSwapChain();
	initSwapChain();

	createCommandPoolBuffers();
}

void Vulkan::waitForDeviceIdle() {
	device.waitIdle();
}

void Vulkan::createCommandPoolBuffers() {
	commandPool.createBuffers(swapChain.getFrameBuffers(), renderPass, swapChain.getExtent(), graphicsPipeline, vertexBuffer, indexBuffer, indexBuffer.getIndicesSize());
}
