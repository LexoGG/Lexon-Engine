#include "IndexBuffer.h"
#include "BufferUtils.h"
#include <iostream>

void IndexBuffer::createIndexBuffer() {
    VkDeviceSize bufferSize = sizeof(vertices[0]) * indices.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    BufferUtils::createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

    void* data;
    vkMapMemory(VulkanContext::getDevice(), stagingBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, indices.data(), (size_t)bufferSize);
    vkUnmapMemory(VulkanContext::getDevice(), stagingBufferMemory);

    BufferUtils::createBuffer(bufferSize, VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, indexBuffer, indexBufferMemory);

    BufferUtils::copyBuffer(stagingBuffer, indexBuffer, bufferSize);

    vkDestroyBuffer(VulkanContext::getDevice(), stagingBuffer, nullptr);
    vkFreeMemory(VulkanContext::getDevice(), stagingBufferMemory, nullptr);
}

void IndexBuffer::bindIndex(VkCommandBuffer commandBuffer) {
    vkCmdBindIndexBuffer(commandBuffer, indexBuffer, 0, VK_INDEX_TYPE_UINT32);
}

void IndexBuffer::destroy(VkDevice device) {
    std::cout << "Buffer no destruido" << std::endl;

    if (indexBuffer != VK_NULL_HANDLE) {
        vkDestroyBuffer(device, indexBuffer, nullptr);
        indexBuffer = VK_NULL_HANDLE;
    }
    if (memory != VK_NULL_HANDLE) {
        vkFreeMemory(device, memory, nullptr);
        memory = VK_NULL_HANDLE;
    }

    BufferUtils::destroyBuffer(device, indexBuffer, memory);
    std::cout << "Buffer destruido" << std::endl;
}


VkBuffer IndexBuffer::indexBuffer = VK_NULL_HANDLE;
