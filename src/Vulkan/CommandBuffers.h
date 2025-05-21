#pragma once

#include "VulkanContext.h"
#include "Pipeline.h"
#include "Swapchain.h"
#include "VertexBuffer.h"
#include <vector>

class CommandBuffers {
public:
    void init(VulkanContext& context, Swapchain& swapchain);
    void cleanup(VulkanContext& context);

    VkCommandBuffer getCommandBuffer(size_t index) const;
    void recordCommandBuffer(VulkanContext& context, Swapchain& swapchain, Pipeline& pipeline, VertexBuffer& vertexBuffer, uint32_t imageIndex, uint32_t frameIndex);



private:
    void createCommandPool(VulkanContext& context);
    void createCommandBuffers(VulkanContext& context);




    VkCommandPool commandPool = VK_NULL_HANDLE;
    std::vector<VkCommandBuffer> commandBuffers;


    static const int MAX_FRAMES_IN_FLIGHT = 2;
};
