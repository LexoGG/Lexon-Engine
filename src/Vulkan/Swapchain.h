// Swapchain.h
#pragma once

#include "VulkanContext.h"
#include "../Core/Window.h"

#include <vector>

class Swapchain {
public:
    void init(VulkanContext& context, Window& window); // ✅ sin renderPass
    void cleanup(VulkanContext& context);
    void recreate(VulkanContext& context, Window& window, VkRenderPass renderPass);

    VkSwapchainKHR getRawSwapchain() const;
    VkExtent2D getExtent() const;
    VkFormat getFormat() const;
    const std::vector<VkImageView>& getImageViews() const;
    const std::vector<VkFramebuffer>& getFramebuffers() const;
    void createFramebuffers(VulkanContext& context, VkRenderPass renderPass);





private:
    void createSwapchain(VulkanContext& context, Window& window);
    void createImageViews(VulkanContext& context);
    void cleanupSwapchain(VulkanContext& context);

    VkSwapchainKHR swapchain;
    std::vector<VkImage> images;
    std::vector<VkImageView> imageViews;
    std::vector<VkFramebuffer> framebuffers;

    VkExtent2D extent;
    VkFormat format;

    friend class Pipeline;
};
