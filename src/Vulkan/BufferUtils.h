#pragma once
#include <vulkan/vulkan.h>

void createBuffer(
    VkDevice device,
    VkPhysicalDevice physicalDevice,
    VkDeviceSize size,
    VkBufferUsageFlags usage,
    VkMemoryPropertyFlags properties,
    VkBuffer& buffer,
    VkDeviceMemory& bufferMemory
);

uint32_t findMemoryType(
    uint32_t typeFilter,
    VkMemoryPropertyFlags properties,
    VkPhysicalDevice physicalDevice
);

void destroyBuffer(VkDevice device, VkBuffer& buffer, VkDeviceMemory& bufferMemory);

void copyBuffer(
    VkDevice device,
    VkCommandPool commandPool,
    VkQueue graphicsQueue,
    VkBuffer srcBuffer,
    VkBuffer dstBuffer,
    VkDeviceSize size
);

