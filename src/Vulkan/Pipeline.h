#pragma once

#include "VulkanContext.h"
#include "Swapchain.h"
#include "Vertex.h"

class Pipeline {
public:
    void init(VulkanContext& context, Swapchain& swapchain);
    void cleanup(VulkanContext& context);

    VkRenderPass getRenderPass() const;
    VkPipeline getGraphicsPipeline() const;
    VkPipelineLayout getPipelineLayout() const;

private:
    void createRenderPass(VulkanContext& context, Swapchain& swapchain);
    void createGraphicsPipeline(VulkanContext& context);
    VkShaderModule createShaderModule(VulkanContext& context, const char* filepath);

    VkRenderPass renderPass = VK_NULL_HANDLE;
    VkPipelineLayout pipelineLayout = VK_NULL_HANDLE;
    VkPipeline graphicsPipeline = VK_NULL_HANDLE;
};

class DescriptorSet {
public:
    void init(VkDevice device, VkDescriptorSetLayout& descriptorSetLayout);
    VkDescriptorSetLayout& getDescriptor();

private:
    VkDescriptorSetLayout descriptorSetLayout;
    VkPipelineLayout pipelineLayout;
};
