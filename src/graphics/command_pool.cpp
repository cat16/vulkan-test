#include "graphics/command_pool.hpp"

void CommandPool::create(vk::PhysicalDevice physicalDevice, vk::SurfaceKHR surface, vk::Device device) {
	SwapchainUtil::QueueFamilyIndices queueFamilyIndices = SwapchainUtil::findQueueFamilies(physicalDevice, surface);

	vk::CommandPoolCreateInfo poolInfo({}, queueFamilyIndices.graphicsFamily);
	device.createCommandPool(&poolInfo, nullptr, &commandPool);

	this->device = device;
}

void CommandPool::createBuffers(std::vector<vk::Framebuffer> frameBuffers, vk::RenderPass renderPass, vk::Extent2D extent, vk::Pipeline pipeline, vk::Buffer vertexBuffer, vk::Buffer indexBuffer, size_t indicesSize) {
	commandBuffers.resize(frameBuffers.size());

	vk::CommandBufferAllocateInfo allocInfo(commandPool, vk::CommandBufferLevel::ePrimary, (uint32_t)commandBuffers.size());
	device.allocateCommandBuffers(&allocInfo, commandBuffers.data());

	for (size_t i = 0; i < commandBuffers.size(); i++) {
		vk::CommandBufferBeginInfo beginInfo = vk::CommandBufferBeginInfo({ vk::CommandBufferUsageFlagBits::eSimultaneousUse }, nullptr);
		commandBuffers[i].begin(beginInfo);

		std::array<float, 4> color = {0.0f, 0.0f, 0.0f, 1.0f};
		vk::ClearValue clearValue = vk::ClearValue(color);
		vk::RenderPassBeginInfo renderPassInfo(renderPass, frameBuffers[i], vk::Rect2D({0, 0}, extent), 1, &clearValue);

		commandBuffers[i].beginRenderPass(&renderPassInfo, vk::SubpassContents::eInline);

		commandBuffers[i].bindPipeline(vk::PipelineBindPoint::eGraphics, pipeline);

		vk::Buffer vertexBuffers[] = { vertexBuffer };
		vk::DeviceSize offsets[] = { 0 };
		commandBuffers[i].bindVertexBuffers(0, 1, vertexBuffers, offsets);
		commandBuffers[i].bindIndexBuffer(indexBuffer, 0, vk::IndexType::eUint16);

		commandBuffers[i].drawIndexed(static_cast<uint32_t>(indicesSize), 1, 0, 0, 0);
		//commandBuffers[i].draw(4, 1, 0, 0);
	//hehe
		commandBuffers[i].endRenderPass();
		commandBuffers[i].end();
	}
}

CommandPool::operator vk::CommandPool() const {
	return commandPool;
}

std::vector<vk::CommandBuffer> CommandPool::getBuffers() {
	return commandBuffers;
}

void CommandPool::destory() {
	device.destroyCommandPool(commandPool, nullptr);
}

void CommandPool::freeBuffers() {
	device.freeCommandBuffers(commandPool, static_cast<uint32_t>(commandBuffers.size()), commandBuffers.data());
}