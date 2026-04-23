#pragma once
#include "../Core/Window.h" 
#include <vulkan/vulkan.h>

class Window;
class VulkanContext;
class Swapchain;

namespace ImGuiVulkan {

//void Init(VulkanContext& context, const Swapchain& swapchain, VkRenderPass renderPass);
void Init(VulkanContext& context, const Swapchain& swapchain, VkRenderPass renderPass);

void Shutdown(VkDevice device);

void BeginFrame();
void EndFrame();

void RenderDrawData(VkCommandBuffer commandBuffer);

void NotifySwapchainImageCount(uint32_t imageCount);

VkDescriptorSet AddTexture(VkSampler sampler, VkImageView imageView,
    VkImageLayout imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

void RemoveTexture(VkDescriptorSet descriptorSet);

}  // namespace ImGuiVulkan
