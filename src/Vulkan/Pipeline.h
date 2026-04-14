#pragma once
#include "UniformBuffer.h"
#include "VulkanContext.h"
#include "Swapchain.h"
#include "Vertex.h"

class Pipeline {
public:
    void init();
    void cleanup(VulkanContext& context);

    static VkRenderPass getRenderPass();
    static VkPipeline getGraphicsPipeline() ;
    static VkPipelineLayout getPipelineLayout() ;

private:
    void createRenderPass();
    void createGraphicsPipeline();
    VkShaderModule createShaderModule(const std::vector<char>& code);

    static VkRenderPass renderPass;
    static VkPipelineLayout pipelineLayout;
    static VkPipeline graphicsPipeline;
};
