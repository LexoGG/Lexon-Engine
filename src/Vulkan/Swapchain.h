// Swapchain.h
#pragma once

#include "VulkanContext.h"
#include "../Core/Window.h"
#include "Pipeline.h"
#include "../Assets/Textures.h"
#include "DephtBuffer.h"
#include <vector>

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete() {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

class Swapchain {
public:
    void init(VulkanContext& context, Window& window); // ✅ sin renderPass
    void cleanup(VulkanContext& context);
    static void recreate();

    static VkExtent2D getExtent() ;
    static VkFormat getFormat() ;
    const std::vector<VkImageView>& getImageViews() const;
    static const std::vector<VkFramebuffer>& getFramebuffers() ;
    static void createFramebuffers();
    static QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
    static VkFramebuffer getIndexFramebuffers(uint32_t imageIndex) ;

    static QueueFamilyIndices getQueueFamilyIndices() { return indices; };
    static VkSwapchainKHR GetSwapchain() { return swapchain; };

    static std::vector<VkImageView> swapChainImageViews;

    static void recreateSwapChain();
    static void createSwapchain();
    static void createImageViews();
    static void cleanupSwapChain();
private:



    static VkSwapchainKHR swapchain;
    static VkSwapchainKHR* swapchainPointer;  // Agregado para obtener un puntero al swapchain
    static std::vector<VkImage> swapChainImages;
    
    static std::vector<VkFramebuffer> swapChainFramebuffers;

    static VkExtent2D swapChainExtent;
    static VkFormat swapChainImageFormat;
    static QueueFamilyIndices indices;


};
