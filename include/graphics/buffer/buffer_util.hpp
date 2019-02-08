#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>

#include <util.hpp>

namespace BufferUtil {
    void createBuffer(vk::Device device, vk::PhysicalDevice physicalDevice, vk::DeviceSize size, vk::BufferUsageFlags usage, vk::MemoryPropertyFlags properties, vk::Buffer& buffer, vk::DeviceMemory& bufferMemory);
    void copyBuffer(vk::Device device, vk::CommandPool commandPool, vk::Queue graphicsQueue, vk::Buffer srcBuffer, vk::Buffer dstBuffer, vk::DeviceSize size);
}