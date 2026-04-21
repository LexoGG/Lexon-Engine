#pragma once
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Swapchain.h"

#include <chrono>
#include <vulkan/vulkan.h>

#include "CommandBuffers.h"
#include "BufferUtils.h"  // Asegúrate de que esto esté presente

# include <math.h>
#include "VulkanContext.h"

#include "Pipeline.h"


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
    //static glm::vec3 CameraPositionInit;
    static glm::vec3 CameraDirectionInit;
    static float rotation[3];
    static float CameraPositionInit[3];
    //stglm::vec3 UniformBuffer::CameraPositionInit = glm::vec3(0.0f, 0.0f, 0.0f);
    //static glm::vec3 objectPosition = glm::vec3(0.0f, 0.0f, 0.0f);

    static float objectPosition[3];
    static float objectScale[3];


private:
    static VkDescriptorSetLayout descriptorSetLayout;
    static std::vector<VkBuffer> uniformBuffers;
    static std::vector<VkDeviceMemory> uniformBuffersMemory;
    VkDeviceSize bufferSize = sizeof(UniformBufferObject);

};

