#pragma once

#include "VulkanContext.h"
#include "Swapchain.h"
#include "Pipeline.h"
#include "CommandBuffers.h"
#include "../Vulkan/UniformBuffer.h"
#include "../ImGui/ImGuiVulkan.h"

#include <vector>

class SyncObjects {
public:
    void createSyncObjects();
    void cleanup(VulkanContext& context);
	static uint32_t getCurrentFrame() { return currentFrame; }

    void drawFrame();

private:

    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;
    
    static uint32_t currentFrame;
    //uint32_t frameIndex = currentFrame;
};
