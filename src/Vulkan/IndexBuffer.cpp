#include "IndexBuffer.h"
#include "BufferUtils.h"

void IndexBuffer::create(VkDevice device, VkPhysicalDevice physicalDevice, const std::vector<uint32_t>& indices) {
    indexCount = static_cast<uint32_t>(indices.size());
    VkDeviceSize bufferSize = sizeof(uint32_t) * indices.size();

    // Aquí puedes usar una función común para crear buffers (como en VertexBuffer)
    createBuffer(
        device,
        physicalDevice,
        bufferSize,
        VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        buffer,
        memory
    );

    void* data;
    vkMapMemory(device, memory, 0, bufferSize, 0, &data);
    memcpy(data, indices.data(), (size_t)bufferSize);
    vkUnmapMemory(device, memory);
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
    destroyBuffer(device, buffer, memory);

}
