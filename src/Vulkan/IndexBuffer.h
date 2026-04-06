#pragma once

#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include "Vertex.h"
#include "../Assets/Square.h"

class IndexBuffer {
public:
    void createIndexBuffer();

    void destroy(VkDevice device);
    void bindIndex(VkCommandBuffer commandBuffer);

    uint32_t getIndexCount() const { return indexCount; }
    static VkBuffer getIndexVertexCount() { return indexBuffer; }

private:
    static VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory = VK_NULL_HANDLE;

    std::vector<VkBuffer> uniformBuffers;
    std::vector<VkDeviceMemory> uniformBuffersMemory;
    std::vector<void*> uniformBuffersMapped;
    VkDeviceMemory memory = VK_NULL_HANDLE;
    uint32_t indexCount = 0;
};
