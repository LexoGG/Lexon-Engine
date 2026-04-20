#pragma once
#include <imgui.h>
#include "../Vulkan/VulkanContext.h"     // para VulkanContext::getDevice()
#include "../Assets/Textures.h" 
#include <array>
#include <stdexcept>
#include <iostream>

class OffscreenRenderer {
public:
    void Init();
    void Resize(uint32_t width, uint32_t height);
    void BeginRenderPass(VkCommandBuffer cmdBuffer);
    void EndRenderPass(VkCommandBuffer cmdBuffer);
    ImTextureID GetImGuiTexture() const { return (ImTextureID)m_ColorImageView; }


    void Cleanup();

    uint32_t GetWidth() const { return m_Width; }
    uint32_t GetHeight() const { return m_Height; }

private:
    // Color attachment
    VkImage m_ColorImage = VK_NULL_HANDLE;
    VkImageView m_ColorImageView = VK_NULL_HANDLE;
    VkDeviceMemory m_ColorMemory = VK_NULL_HANDLE;

    // Depth attachment
    VkImage m_DepthImage = VK_NULL_HANDLE;
    VkImageView m_DepthImageView = VK_NULL_HANDLE;
    VkDeviceMemory m_DepthMemory = VK_NULL_HANDLE;

    VkFramebuffer m_Framebuffer = VK_NULL_HANDLE;
    VkRenderPass m_OffscreenRenderPass = VK_NULL_HANDLE;

    uint32_t m_Width = 0;
    uint32_t m_Height = 0;

    void CreateRenderPass();
    void CreateResources();
    void CleanupResources();
};