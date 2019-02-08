#include "graphics/buffer/buffer_util.hpp"

void BufferUtil::createBuffer(vk::Device device, vk::PhysicalDevice physicalDevice, vk::DeviceSize size, vk::BufferUsageFlags usage, vk::MemoryPropertyFlags properties, vk::Buffer &buffer, vk::DeviceMemory &bufferMemory) {
	vk::BufferCreateInfo bufferInfo({}, size, usage, vk::SharingMode::eExclusive);

	device.createBuffer(&bufferInfo, nullptr, &buffer);

	vk::MemoryRequirements memRequirements;
	device.getBufferMemoryRequirements(buffer, &memRequirements);

	vk::MemoryAllocateInfo allocInfo(memRequirements.size, Util::findMemoryType(physicalDevice, memRequirements.memoryTypeBits, properties));

	device.allocateMemory(&allocInfo, nullptr, &bufferMemory);

	device.bindBufferMemory(buffer, bufferMemory, 0);
}

void BufferUtil::copyBuffer(vk::Device device, vk::CommandPool commandPool, vk::Queue graphicsQueue, vk::Buffer srcBuffer, vk::Buffer dstBuffer, vk::DeviceSize size) {
	vk::CommandBufferAllocateInfo allocInfo(commandPool, vk::CommandBufferLevel::ePrimary, 1);

	vk::CommandBuffer commandBuffer;
	device.allocateCommandBuffers(&allocInfo, &commandBuffer);

	vk::CommandBufferBeginInfo beginInfo(vk::CommandBufferUsageFlagBits::eOneTimeSubmit);

	commandBuffer.begin(&beginInfo);

	vk::BufferCopy copyRegion(0, 0, size);
	commandBuffer.copyBuffer(srcBuffer, dstBuffer, 1, &copyRegion);

	commandBuffer.end();

	vk::SubmitInfo submitInfo(0, nullptr, nullptr, 1, &commandBuffer);

	graphicsQueue.submit(1, &submitInfo, nullptr);
	graphicsQueue.waitIdle();

	device.freeCommandBuffers(commandPool, 1, &commandBuffer);
}
