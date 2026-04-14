#include "IndexBuffer.h"

#include <iostream>

void IndexBuffer::createIndexBuffer()
{
    if (LoaderModels::indices.empty())
    {
        // Evita crear buffer vacío (opcional pero recomendado)
        indexBuffer = VK_NULL_HANDLE;
        indexBufferMemory = VK_NULL_HANDLE;
        return;
    }

    VkDeviceSize bufferSize = sizeof(LoaderModels::indices[0]) * LoaderModels::indices.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;

    BufferUtils::createBuffer(
        bufferSize,
        VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        stagingBuffer,
        stagingBufferMemory);

    void* data = nullptr;                    // ← mejor inicializado

    VkResult result = vkMapMemory(
        VulkanContext::getDevice(),
        stagingBufferMemory,
        0,
        bufferSize,
        0,
        &data);

    if (result != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to map staging buffer memory! Error: " + std::to_string(result));
    }

    memcpy(data, LoaderModels::indices.data(), static_cast<size_t>(bufferSize));

    vkUnmapMemory(VulkanContext::getDevice(), stagingBufferMemory);

    // Buffer final en GPU
    BufferUtils::createBuffer(
        bufferSize,
        VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
        indexBuffer,
        indexBufferMemory);

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
