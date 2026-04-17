// VertexBuffer.cpp
#include "VertexBuffer.h"
#include <iomanip> 
#include <cstring>
#include <stdexcept>
#include <iostream>

VkBuffer VertexBuffer::vertexBuffer = VK_NULL_HANDLE;

void VertexBuffer::createVertexBuffer() {
    vertexBufferSize = sizeof(LoaderModels::vertices[0]) * LoaderModels::vertices.size();

    // 1. Staging buffer persistente (solo se crea una vez)
    BufferUtils::createBuffer(vertexBufferSize,
        VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        stagingBuffer, stagingBufferMemory);

    // 2. Vertex buffer en GPU (device-local)
    BufferUtils::createBuffer(vertexBufferSize,
        VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
        vertexBuffer, vertexBufferMemory);

    // Copia inicial
    update();   // reutilizamos la misma función que usarás después

}

void VertexBuffer::destroy() {

    vkDestroyBuffer(VulkanContext::getDevice(), vertexBuffer, nullptr);

}

void VertexBuffer::bind(VkCommandBuffer commandBuffer) {
    VkBuffer vertexBuffers[] = { vertexBuffer };
    VkDeviceSize offsets[] = { 0 };
    vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);
}

void VertexBuffer::update() {
    if (vertexBufferSize == 0) return;

    // Mapear staging y copiar datos nuevos desde LoaderModels::vertices
    void* data;
    vkMapMemory(VulkanContext::getDevice(), stagingBufferMemory, 0, vertexBufferSize, 0, &data);
    memcpy(data, LoaderModels::vertices.data(), static_cast<size_t>(vertexBufferSize));
    vkUnmapMemory(VulkanContext::getDevice(), stagingBufferMemory);

    // Copiar al buffer del GPU
    BufferUtils::copyBuffer(stagingBuffer, vertexBuffer, vertexBufferSize);
};

VkDeviceMemory VertexBuffer::vertexBufferMemory = VK_NULL_HANDLE;
VkBuffer       VertexBuffer::stagingBuffer = VK_NULL_HANDLE;
VkDeviceMemory VertexBuffer::stagingBufferMemory = VK_NULL_HANDLE;
VkDeviceSize   VertexBuffer::vertexBufferSize = 0;