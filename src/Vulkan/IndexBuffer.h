#pragma once

#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include "Vertex.h"

class IndexBuffer {
public:
    void create(VkDevice device, VkPhysicalDevice physicalDevice, const std::vector<uint32_t>& indices);
    void createUniformBuffer();
    void destroy(VkDevice device);
    void bind(VkCommandBuffer commandBuffer);

    uint32_t getIndexCount() const { return indexCount; }

private:
    VkBuffer buffer = VK_NULL_HANDLE;
    VkDeviceMemory indexBufferMemory;

    std::vector<VkBuffer> uniformBuffers;
    std::vector<VkDeviceMemory> uniformBuffersMemory;
    std::vector<void*> uniformBuffersMapped;
    VkDeviceMemory memory = VK_NULL_HANDLE;
    uint32_t indexCount = 0;
};
