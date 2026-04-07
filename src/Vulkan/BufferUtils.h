#pragma once

#include "VulkanContext.h"
#include <vulkan/vulkan.h>
#include "CommandBuffers.h"
#include "BufferUtils.h"

class BufferUtils{
	public:
        static void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);

        static uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

        static void destroyBuffer(VkDevice device, VkBuffer& buffer, VkDeviceMemory& bufferMemory);


        static VkCommandBuffer beginSingleTimeCommands();
        static void endSingleTimeCommands(VkCommandBuffer commandBuffer);
        static void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);




};