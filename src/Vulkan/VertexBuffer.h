// VertexBuffer.h
#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include "Vertex.h"
#include "VulkanContext.h"
#include "../Assets/Square.h"
#include "BufferUtils.h"


class VertexBuffer {
public:

    void createVertexBuffer();
    void destroy();
    void bind(VkCommandBuffer commandBuffer);
    static void update();

    static VkBuffer getBuffer()  { return vertexBuffer; }
    static VkDeviceMemory getvertexbuffermemory() { return vertexBufferMemory; }
    uint32_t getVertexCount() const { return vertexCount; }

private:
    static VkBuffer vertexBuffer;
    static VkDeviceMemory vertexBufferMemory;
    uint32_t vertexCount = 0;
    static VkBuffer       stagingBuffer ;
    static VkDeviceMemory stagingBufferMemory;
    static VkDeviceSize   vertexBufferSize;
};
