#include "UniformBuffer.h"
#include "../Renderer/StaticMesh.h"


void UniformBuffer::createDescriptorSetLayout (VkDevice device) {
    VkDescriptorSetLayoutBinding uboLayoutBinding{};
    uboLayoutBinding.binding = 0;
    uboLayoutBinding.descriptorCount = 1;
    uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    uboLayoutBinding.pImmutableSamplers = nullptr;
    uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

    VkDescriptorSetLayoutBinding samplerLayoutBinding{};
    samplerLayoutBinding.binding = 1;
    samplerLayoutBinding.descriptorCount = 1;
    samplerLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    samplerLayoutBinding.pImmutableSamplers = nullptr;
    samplerLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;

    std::array<VkDescriptorSetLayoutBinding, 2> bindings = { uboLayoutBinding, samplerLayoutBinding };

    VkDescriptorSetLayoutCreateInfo layoutInfo{};
    layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    layoutInfo.bindingCount = static_cast<uint32_t>(bindings.size());
    layoutInfo.pBindings = bindings.data();

    if (vkCreateDescriptorSetLayout(device, &layoutInfo, nullptr, &descriptorSetLayout) != VK_SUCCESS) {
        throw std::runtime_error("failed to create descriptor set layout!");
    }
}

void UniformBuffer::destroyDescriptorSet(VkDevice device) {

    vkDestroyDescriptorSetLayout(device, descriptorSetLayout, nullptr);

};

void UniformBuffer::createUniformBuffers() {
    VkDeviceSize bufferSize = sizeof(UniformBufferObject);

    uniformBuffers.resize(MAX_FRAMES_IN_FLIGHT);
    uniformBuffersMemory.resize(MAX_FRAMES_IN_FLIGHT);
    uniformBuffersMapped.resize(MAX_FRAMES_IN_FLIGHT);

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        BufferUtils::createBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, uniformBuffers[i], uniformBuffersMemory[i]);

        vkMapMemory(VulkanContext::getDevice(), uniformBuffersMemory[i], 0, bufferSize, 0, &uniformBuffersMapped[i]);
    }
}


void UniformBuffer::updateUniformBuffer(uint32_t currentImage) {
    static auto startTime = std::chrono::high_resolution_clock::now();

    auto currentTime = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

    UniformBufferObject ubo{};
    

    StaticMesh::getModelMatrix(ubo.model);



    glm::mat4 posmodelz = glm::lookAt(CameraDirectionInit, glm::vec3(CameraPositionInit[2]), glm::vec3(0.0f, 0.0f, 1.0f));
    ubo.view = posmodelz;


    ubo.proj = glm::perspective(glm::radians(45.0f), Swapchain::getExtent().width / (float)Swapchain::getExtent().height, 0.1f, 10.0f);
    ubo.proj[1][1] *= -1;

    memcpy(uniformBuffersMapped[currentImage], &ubo, sizeof(ubo));
}

VkDescriptorSetLayout UniformBuffer::getdescriptorset() {
    return descriptorSetLayout;
};

VkDescriptorSetLayout* UniformBuffer::getdescriptorsetPointer() {
    return &descriptorSetLayout;
};


std::vector<VkBuffer> UniformBuffer::getuniformBuffers() {
	return uniformBuffers;
};

std::vector<VkDeviceMemory> UniformBuffer::getuniformBuffersMemory() {
    return uniformBuffersMemory;
};



VkDeviceSize UniformBuffer::getBufferSize() {
    return bufferSize;
};

VkDescriptorSetLayout UniformBuffer::descriptorSetLayout;
std::vector<VkBuffer> UniformBuffer::uniformBuffers;
std::vector<void*> UniformBuffer::uniformBuffersMapped;
std::vector<VkDeviceMemory> UniformBuffer::uniformBuffersMemory;
float UniformBuffer::rotation[3] = { 0.0f, 0.0f, 0.0f };
float UniformBuffer::CameraPositionInit[3] = {0.0f, 0.0f, 0.0f};
glm::vec3 UniformBuffer::CameraDirectionInit = glm::vec3(2.0f, 2.0f, 2.0f);

float UniformBuffer::objectPosition[3] = { 0.0f, 0.0f, 0.0f };
float UniformBuffer::objectScale[3] = { 1.0f, 1.0f, 1.0f };

