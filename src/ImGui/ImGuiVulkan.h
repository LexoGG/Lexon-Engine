#pragma once

#include <vulkan/vulkan.h>

class Window;
class VulkanContext;
class Swapchain;

namespace ImGuiVulkan {

void Init(Window& window, VulkanContext& context, const Swapchain& swapchain, VkRenderPass renderPass);
void Shutdown(VkDevice device);

void BeginFrame();
void EndFrame();

void RenderDrawData(VkCommandBuffer commandBuffer);

void NotifySwapchainImageCount(uint32_t imageCount);

}  // namespace ImGuiVulkan
