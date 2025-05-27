#pragma once

#include "VulkanContext.h"
#include "Swapchain.h"
#include "Pipeline.h"
#include "CommandBuffers.h"


#include <vector>

class SyncObjects {
public:
    void init(VulkanContext& context);
    void cleanup(VulkanContext& context);

    void drawFrame(VulkanContext& context, Swapchain& swapchain, Pipeline& pipeline, CommandBuffers& commandBuffers, VertexBuffer& vertexBuffer, IndexBuffer& indexBuffer, Window& window, VkRenderPass renderPass);

private:
    static const int MAX_FRAMES_IN_FLIGHT = 2;

    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;

    uint32_t currentFrame = 0;
};
