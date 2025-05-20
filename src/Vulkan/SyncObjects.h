#pragma once

#include "VulkanContext.h"
#include "Swapchain.h"
#include "Pipeline.h"
#include "CommandBuffers.h"
#include "../Core/Config.h"

#include <vector>

class SyncObjects {
public:
    void init(VulkanContext& context);
    void cleanup(VulkanContext& context);

    void drawFrame(VulkanContext& context, Swapchain& swapchain, Pipeline& pipeline, CommandBuffers& commandBuffers, VertexBuffer& vertexBuffer, Window& window, VkRenderPass renderPass);

private:

    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;

    uint32_t currentFrame = 0;
};
