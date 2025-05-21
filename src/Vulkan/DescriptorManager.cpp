#include "DescriptorManager.h"
#include <stdexcept>

void DescriptorManager::init(VkDevice device, VkDescriptorSetLayout layout, uint32_t frameCount) {
    VkDescriptorPoolSize poolSize{};
    poolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    poolSize.descriptorCount = frameCount;

    VkDescriptorPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    poolInfo.poolSizeCount = 1;
    poolInfo.pPoolSizes = &poolSize;
    poolInfo.maxSets = frameCount;

    if (vkCreateDescriptorPool(device, &poolInfo, nullptr, &descriptorPool) != VK_SUCCESS) {
        throw std::runtime_error("failed to create descriptor pool!");
    }

    std::vector<VkDescriptorSetLayout> layouts(frameCount, layout);
    VkDescriptorSetAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfo.descriptorPool = descriptorPool;
    allocInfo.descriptorSetCount = frameCount;
    allocInfo.pSetLayouts = layouts.data();

    descriptorSets.resize(frameCount);
    if (vkAllocateDescriptorSets(device, &allocInfo, descriptorSets.data()) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate descriptor sets!");
    }
}

void DescriptorManager::cleanup(VkDevice device) {
    vkDestroyDescriptorPool(device, descriptorPool, nullptr);
}

VkDescriptorSet DescriptorManager::getSet(uint32_t frameIndex) const {
    return descriptorSets[frameIndex];
}
