#include "graphics/buffer/vertex.hpp"

vk::VertexInputBindingDescription Vertex::getBindingDescription()
{
	vk::VertexInputBindingDescription bindingDescription(0, sizeof(Vertex), vk::VertexInputRate::eVertex);
	return bindingDescription;
}

std::array<vk::VertexInputAttributeDescription, 2> Vertex::getAttributeDescriptions()
{
	std::array<vk::VertexInputAttributeDescription, 2> attributeDescriptions = {};
	attributeDescriptions[0] = vk::VertexInputAttributeDescription(0, 0, vk::Format::eR32G32Sfloat, offsetof(Vertex, pos));
	attributeDescriptions[1] = vk::VertexInputAttributeDescription(1, 0, vk::Format::eR32G32B32Sfloat, offsetof(Vertex, color));

	return attributeDescriptions;
}

void VertexBuffer::create(vk::Device device, vk::CommandPool commandPool, vk::Queue graphicsQueue, vk::PhysicalDevice physicalDevice, std::vector<Vertex> vertices)
{
	vk::DeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();

	vk::Buffer stagingBuffer;
	vk::DeviceMemory stagingBufferMemory;

	BufferUtil::createBuffer(device, physicalDevice, bufferSize, vk::BufferUsageFlagBits::eTransferSrc, vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent, stagingBuffer, stagingBufferMemory);

	void *data;
	device.mapMemory(stagingBufferMemory, 0, bufferSize, {}, &data);
	memcpy(data, vertices.data(), (size_t)bufferSize);
	device.unmapMemory(stagingBufferMemory);

	BufferUtil::createBuffer(device, physicalDevice, bufferSize, vk::BufferUsageFlagBits::eTransferDst | vk::BufferUsageFlagBits::eVertexBuffer, vk::MemoryPropertyFlagBits::eDeviceLocal, buffer, bufferMemory);
	BufferUtil::copyBuffer(device, commandPool, graphicsQueue, stagingBuffer, buffer, bufferSize);

	device.destroyBuffer(stagingBuffer, nullptr);
    device.freeMemory(stagingBufferMemory, nullptr);

	this->device = device;

	this->verticesSize = vertices.size();
}

VertexBuffer::operator vk::Buffer() const
{
	return buffer;
}

size_t VertexBuffer::getVerticesSize()
{
	return verticesSize;
}

void VertexBuffer::destroy()
{
	device.destroyBuffer(buffer, nullptr);
	device.freeMemory(bufferMemory, nullptr);
}