#pragma once
#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Swapchain.h"

#include <chrono>
#include <vulkan/vulkan.h>


struct UniformBufferObject {
    alignas(16) glm::mat4 model;
    alignas(16) glm::mat4 view;
    alignas(16) glm::mat4 proj;
};

class UniformBuffer {

public:
    static void createDescriptorSetLayout(VkDevice device);
    void createUniformBuffers();
    static void updateUniformBuffer(uint32_t currentImage);
    static VkDescriptorSetLayout getdescriptorset();
    static VkDescriptorSetLayout* getdescriptorsetPointer();

    static std::vector<VkBuffer> getuniformBuffers();
    void destroyDescriptorSet(VkDevice device);
    VkDeviceSize getBufferSize();
    static std::vector<void*> uniformBuffersMapped;
    static std::vector<VkDeviceMemory> getuniformBuffersMemory();


private:
    static VkDescriptorSetLayout descriptorSetLayout;
    static std::vector<VkBuffer> uniformBuffers;
    static std::vector<VkDeviceMemory> uniformBuffersMemory;
    VkDeviceSize bufferSize = sizeof(UniformBufferObject);

};

