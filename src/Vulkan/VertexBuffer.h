// VertexBuffer.h
#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include "Vertex.h"

class VertexBuffer {
public:
    void create(VkDevice device, VkPhysicalDevice physicalDevice, const std::vector<Vertex>& vertices);
    void createIndexBuffer();
    void destroy(VkDevice device);
    void bind(VkCommandBuffer commandBuffer);

    VkBuffer getBuffer() const { return buffer; }
    uint32_t getVertexCount() const { return vertexCount; }

private:
    VkBuffer buffer = VK_NULL_HANDLE;
    VkDeviceMemory memory = VK_NULL_HANDLE;
    uint32_t vertexCount = 0;
    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;
};