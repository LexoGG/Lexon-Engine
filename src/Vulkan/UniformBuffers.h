#pragma once
#include <vulkan/vulkan.h>
#include <vector>

class UniformBuffers {
public:
    void init(VkDevice device, VkPhysicalDevice physicalDevice, size_t bufferSize, uint32_t frameCount);
    void cleanup(VkDevice device);

    VkBuffer getBuffer(uint32_t frameIndex) const;
    VkDeviceMemory getMemory(uint32_t frameIndex) const;

private:
    std::vector<VkBuffer> buffers;
    std::vector<VkDeviceMemory> memories;
};
