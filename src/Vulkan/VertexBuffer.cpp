// VertexBuffer.cpp
#include "VertexBuffer.h"
#include <iomanip> 
#include <cstring>
#include <stdexcept>
#include <iostream>

VkBuffer VertexBuffer::vertexBuffer = VK_NULL_HANDLE;

void VertexBuffer::createVertexBuffer() {
    VkDeviceSize bufferSize = sizeof(LoaderModels::vertices[0]) * LoaderModels::vertices.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    BufferUtils::createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

    void* data;
    vkMapMemory(VulkanContext::getDevice(), stagingBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, LoaderModels::vertices.data(), (size_t)bufferSize);
    vkUnmapMemory(VulkanContext::getDevice(), stagingBufferMemory);

    BufferUtils::createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vertexBuffer, vertexBufferMemory);

    BufferUtils::copyBuffer(stagingBuffer, vertexBuffer, bufferSize);

    vkDestroyBuffer(VulkanContext::getDevice(), stagingBuffer, nullptr);
    vkFreeMemory(VulkanContext::getDevice(), stagingBufferMemory, nullptr);

}

void VertexBuffer::destroy() {

    vkDestroyBuffer(VulkanContext::getDevice(), vertexBuffer, nullptr);

}

void VertexBuffer::bind(VkCommandBuffer commandBuffer) {
    VkBuffer vertexBuffers[] = { vertexBuffer };
    VkDeviceSize offsets[] = { 0 };


    vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);
}


VkDeviceMemory VertexBuffer::vertexBufferMemory = VK_NULL_HANDLE;