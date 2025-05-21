#pragma once
#include <vulkan/vulkan.h>
#include <vector>

class DescriptorManager {
public:
    void init(VkDevice device, VkDescriptorSetLayout layout, uint32_t frameCount);
    void cleanup(VkDevice device);

    VkDescriptorSet getSet(uint32_t frameIndex) const;
    std::vector<VkDescriptorSet> descriptorSets;

private:
    VkDescriptorPool descriptorPool;
};
