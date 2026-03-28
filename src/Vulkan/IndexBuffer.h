#pragma once

#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include "Vertex.h"

class IndexBuffer {
public:
    void create(VkDevice device, VkPhysicalDevice physicalDevice,
        VkCommandPool commandPool, VkQueue graphicsQueue,
        const std::vector<uint32_t>& indices);

    VkBuffer getBuffer() const { return buffer; }
    uint32_t getIndexCount() const { return indexCount; }

    void bind(VkCommandBuffer commandBuffer);   // ✅ AÑADIR
    void destroy(VkDevice device);

private:
    VkBuffer buffer = VK_NULL_HANDLE;
    VkDeviceMemory memory = VK_NULL_HANDLE;
    uint32_t indexCount = 0;
};
