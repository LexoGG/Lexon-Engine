#include "UniformBuffers.h"
#include <stdexcept>

void UniformBuffers::init(VkDevice device, VkPhysicalDevice physicalDevice, size_t bufferSize, uint32_t frameCount) {
    buffers.resize(frameCount);
    memories.resize(frameCount);

    for (size_t i = 0; i < frameCount; ++i) {
        VkBufferCreateInfo bufferInfo{};
        bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bufferInfo.size = bufferSize;
        bufferInfo.usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
        bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        if (vkCreateBuffer(device, &bufferInfo, nullptr, &buffers[i]) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create uniform buffer");
        }

        VkMemoryRequirements memRequirements;
        vkGetBufferMemoryRequirements(device, buffers[i], &memRequirements);

        VkMemoryAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        allocInfo.allocationSize = memRequirements.size;

        VkPhysicalDeviceMemoryProperties memProperties;
        vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);

        for (uint32_t j = 0; j < memProperties.memoryTypeCount; j++) {
            if ((memRequirements.memoryTypeBits & (1 << j)) &&
                (memProperties.memoryTypes[j].propertyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) &&
                (memProperties.memoryTypes[j].propertyFlags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)) {
                allocInfo.memoryTypeIndex = j;
                break;
            }
        }

        if (vkAllocateMemory(device, &allocInfo, nullptr, &memories[i]) != VK_SUCCESS) {
            throw std::runtime_error("Failed to allocate uniform buffer memory");
        }

        vkBindBufferMemory(device, buffers[i], memories[i], 0);
    }
}

void UniformBuffers::cleanup(VkDevice device) {
    for (size_t i = 0; i < buffers.size(); ++i) {
        vkDestroyBuffer(device, buffers[i], nullptr);
        vkFreeMemory(device, memories[i], nullptr);
    }
}

VkBuffer UniformBuffers::getBuffer(uint32_t frameIndex) const {
    return buffers[frameIndex];
}

VkDeviceMemory UniformBuffers::getMemory(uint32_t frameIndex) const {
    return memories[frameIndex];
}
