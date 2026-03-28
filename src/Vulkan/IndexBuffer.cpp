#include "IndexBuffer.h"
#include "BufferUtils.h"
#include <iostream>

void IndexBuffer::create(VkDevice device, VkPhysicalDevice physicalDevice,
    VkCommandPool commandPool, VkQueue graphicsQueue,
    const std::vector<uint32_t>& indices) {

    indexCount = static_cast<uint32_t>(indices.size());
    VkDeviceSize bufferSize = sizeof(uint32_t) * indexCount;

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;

    // Crear staging buffer (memoria CPU visible)
    createBuffer(device, physicalDevice, bufferSize,
        VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        stagingBuffer, stagingBufferMemory);

    void* data;
    vkMapMemory(device, stagingBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, indices.data(), (size_t)bufferSize);
    vkUnmapMemory(device, stagingBufferMemory);

    // Crear index buffer (memoria GPU)
    createBuffer(device, physicalDevice, bufferSize,
        VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
        buffer, memory);

    // Copiar datos del staging al index buffer
    copyBuffer(device, commandPool, graphicsQueue, stagingBuffer, buffer, bufferSize);

    // Liberar staging
    vkDestroyBuffer(device, stagingBuffer, nullptr);
    vkFreeMemory(device, stagingBufferMemory, nullptr);

    std::cout << "[INFO] IndexBuffer creado correctamente. Índices: " << indexCount << std::endl;
}

void IndexBuffer::bind(VkCommandBuffer commandBuffer) {
    vkCmdBindIndexBuffer(commandBuffer, buffer, 0, VK_INDEX_TYPE_UINT32);
}

void IndexBuffer::destroy(VkDevice device) {
    if (buffer != VK_NULL_HANDLE) {
        vkDestroyBuffer(device, buffer, nullptr);
        buffer = VK_NULL_HANDLE;
    }
    if (memory != VK_NULL_HANDLE) {
        vkFreeMemory(device, memory, nullptr);
        memory = VK_NULL_HANDLE;
    }
}
