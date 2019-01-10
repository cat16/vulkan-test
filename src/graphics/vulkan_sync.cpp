#include "graphics/vulkan_sync.hpp"

void Sync::create(vk::Device device) {
	imageAvailableSemaphores.resize(Game::MAX_FRAMES_IN_FLIGHT);
	renderFinishedSemaphores.resize(Game::MAX_FRAMES_IN_FLIGHT);
	inFlightFences.resize(Game::MAX_FRAMES_IN_FLIGHT);

	vk::SemaphoreCreateInfo semaphoreInfo = vk::SemaphoreCreateInfo(vk::SemaphoreCreateFlagBits());

	vk::FenceCreateInfo fenceInfo(vk::FenceCreateFlagBits::eSignaled);

	for (size_t i = 0; i < Game::MAX_FRAMES_IN_FLIGHT; i++) {
		device.createSemaphore(&semaphoreInfo, nullptr, &imageAvailableSemaphores[i]);
		device.createSemaphore(&semaphoreInfo, nullptr, &renderFinishedSemaphores[i]);
		device.createFence(&fenceInfo, nullptr, &inFlightFences[i]);
	}

	this->device = device;
}

void Sync::nextFrame() {
	currentFrame = (currentFrame + 1) % Game::MAX_FRAMES_IN_FLIGHT;
}

void Sync::waitForFences() {
	device.waitForFences(1, &inFlightFences[currentFrame], VK_TRUE, std::numeric_limits<uint64_t>::max());
}

void Sync::resetFences() {
	device.resetFences(1, &inFlightFences[currentFrame]);
}

vk::Semaphore Sync::getImageAvailableSemaphore() {
	return imageAvailableSemaphores[currentFrame];
}

vk::Semaphore Sync::getRenderFinishedSemaphore() {
	return renderFinishedSemaphores[currentFrame];
}

vk::Fence Sync::getInFlightFence() {
	return inFlightFences[currentFrame];
}

void Sync::destroy() {
	for (size_t i = 0; i < Game::MAX_FRAMES_IN_FLIGHT; i++) {
		device.destroySemaphore(renderFinishedSemaphores[i]);
		device.destroySemaphore(imageAvailableSemaphores[i]);
		device.destroyFence(inFlightFences[i]);
	}
}
