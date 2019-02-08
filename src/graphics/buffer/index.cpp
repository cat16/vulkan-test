#include "graphics/buffer/index.hpp"
//somewhere within this method lies a hidden error ri
void IndexBuffer::create(vk::Device device, vk::CommandPool commandPool, vk::Queue graphicsQueue, vk::PhysicalDevice physicalDevice, std::vector<uint16_t> indices) {
	vk::DeviceSize bufferSize = sizeof(indices[0]) * indices.size();

	vk::Buffer stagingBuffer;
	vk::DeviceMemory stagingBufferMemory;
	BufferUtil::createBuffer(device, physicalDevice, bufferSize, vk::BufferUsageFlagBits::eTransferSrc, vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent, stagingBuffer, stagingBufferMemory);

	void *data;
	device.mapMemory(stagingBufferMemory, 0, bufferSize, {}, &data);
	memcpy(data, indices.data(), (size_t)bufferSize);
	device.unmapMemory(stagingBufferMemory);

	BufferUtil::createBuffer(device, physicalDevice, bufferSize, vk::BufferUsageFlagBits::eTransferDst | vk::BufferUsageFlagBits::eIndexBuffer, vk::MemoryPropertyFlagBits::eDeviceLocal, buffer, bufferMemory);
	BufferUtil::copyBuffer(device, commandPool, graphicsQueue, stagingBuffer, buffer, bufferSize);

	device.destroyBuffer(stagingBuffer, nullptr);
    device.freeMemory(stagingBufferMemory, nullptr);

	this->device = device;

	this->indicesSize = indices.size();
}

IndexBuffer::operator vk::Buffer() const {
	return buffer;
}

size_t IndexBuffer::getIndicesSize()
{
	return indicesSize;
}

void IndexBuffer::destroy() {
	device.destroyBuffer(buffer, nullptr);
	device.freeMemory(bufferMemory, nullptr);
}