#include "graphics/vertex.hpp"

vk::VertexInputBindingDescription Vertex::getBindingDescription() {
	vk::VertexInputBindingDescription bindingDescription(0, sizeof(Vertex), vk::VertexInputRate::eVertex);
	return bindingDescription;
}

std::array<vk::VertexInputAttributeDescription, 2> Vertex::getAttributeDescriptions() {
	std::array<vk::VertexInputAttributeDescription, 2> attributeDescriptions = {};
	attributeDescriptions[0] = vk::VertexInputAttributeDescription(0, 0, vk::Format::eR32G32Sfloat, offsetof(Vertex, pos));
	attributeDescriptions[1] = vk::VertexInputAttributeDescription(0, 1, vk::Format::eR32G32B32Sfloat, offsetof(Vertex, color));

	return attributeDescriptions;
}

void VertexBuffer::create(vk::Device device, vk::PhysicalDevice physicalDevice, std::vector<Vertex> vertices) {
	vk::BufferCreateInfo bufferInfo({}, sizeof(vertices[0]) * vertices.size(), vk::BufferUsageFlagBits::eVertexBuffer, vk::SharingMode::eExclusive);

	device.createBuffer(&bufferInfo, nullptr, &buffer);

	vk::MemoryRequirements memRequirements;
	device.getBufferMemoryRequirements(buffer, &memRequirements);

	vk::MemoryAllocateInfo allocInfo(memRequirements.size, Util::findMemoryType(physicalDevice, memRequirements.memoryTypeBits, vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent));

	device.allocateMemory(&allocInfo, nullptr, &bufferMemory);

	device.bindBufferMemory(buffer, bufferMemory, 0);

	void* data;
	device.mapMemory(bufferMemory, 0, bufferInfo.size, {}, &data);
	memcpy(data, vertices.data(), (size_t)bufferInfo.size);
	device.unmapMemory(bufferMemory);

	this->device = device;

	this->verticesSize = vertices.size();
}

VertexBuffer::operator vk::Buffer() const {
	return buffer;
}

size_t VertexBuffer::getVerticesSize()
{
	return verticesSize;
}

void VertexBuffer::destroy() {
	device.destroyBuffer(buffer, nullptr);
	device.freeMemory(bufferMemory, nullptr);
}