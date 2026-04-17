#pragma once

#include "VulkanContext.h"
#include "Pipeline.h"
#include "Swapchain.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include <vector>

#include "SyncObjects.h"
#include "../ImGui/ImGuiVulkan.h"
#include "../Vulkan/DescriptorPool.h"



class CommandBuffers {
public:
    void init();
    void cleanup(VulkanContext& context);

    static VkCommandBuffer getCommandBuffer(size_t index);
    static void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
    static VkCommandPool GetCommandPool() { return commandPool; };
    void createCommandBuffers();



private:
    void createCommandPool();





    static VkCommandPool commandPool;
    static std::vector<VkCommandBuffer> commandBuffers;


};
