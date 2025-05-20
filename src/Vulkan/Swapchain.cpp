// Swapchain.cpp
#include "Swapchain.h"
#include <stdexcept>
#include <iostream>

void Swapchain::init(VulkanContext& context, Window& window) {
    createSwapchain(context, window);
    createImageViews(context);

}

void Swapchain::cleanup(VulkanContext& context) {
    cleanupSwapchain(context);
}

void Swapchain::recreate(VulkanContext& context, Window& window, VkRenderPass renderPass) {
    int width = 0, height = 0;
    while (width == 0 || height == 0) {
        glfwGetFramebufferSize(window.getGLFWwindow(), &width, &height);
        glfwWaitEvents();
    }

    vkDeviceWaitIdle(context.getDevice());
    cleanupSwapchain(context);
    createSwapchain(context, window);
    createImageViews(context);
    createFramebuffers(context, renderPass); 
}

VkSwapchainKHR Swapchain::getRawSwapchain() const {
    return swapchain;
}

VkSurfaceFormatKHR chooseSwapSurfaceFormat(VkPhysicalDevice device, VkSurfaceKHR surface) {
    uint32_t formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

    std::vector<VkSurfaceFormatKHR> formats(formatCount);
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, formats.data());

    for (const auto& availableFormat : formats) {
        if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB &&
            availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
            return availableFormat;
        }
    }

    return formats[0]; // fallback seguro
}

void Swapchain::createSwapchain(VulkanContext& context, Window& window) {
    VkSurfaceCapabilitiesKHR capabilities;
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(context.getPhysicalDevice(), context.getSurface(), &capabilities);

    VkSurfaceFormatKHR chosenFormat = chooseSwapSurfaceFormat(context.getPhysicalDevice(), context.getSurface());
    format = chosenFormat.format;

    // Validar extent correctamente
    if (capabilities.currentExtent.width == UINT32_MAX) {
        int width, height;
        glfwGetFramebufferSize(window.getGLFWwindow(), &width, &height);
        extent = { static_cast<uint32_t>(width), static_cast<uint32_t>(height) };
    }
    else {
        extent = capabilities.currentExtent;
    }

    // Elegir número de imágenes
    uint32_t imageCount = capabilities.minImageCount + 1;
    if (capabilities.maxImageCount > 0 && imageCount > capabilities.maxImageCount) {
        imageCount = capabilities.maxImageCount;
    }

    // Manejar familias de colas
    auto indices = context.findQueueFamilies(context.getPhysicalDevice());
    uint32_t queueFamilyIndices[] = {
        indices.graphicsFamily.value(),
        indices.presentFamily.value()
    };

    // Validar soporte de presentación
    VkBool32 presentSupport = false;
    vkGetPhysicalDeviceSurfaceSupportKHR(context.getPhysicalDevice(), indices.presentFamily.value(), context.getSurface(), &presentSupport);
    std::cout << "Present support: " << presentSupport << "\n";

    if (!presentSupport) {
        throw std::runtime_error("Device does not support presenting to the surface.");
    }

    // Crear swapchain
    VkSwapchainCreateInfoKHR createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = context.getSurface();
    createInfo.minImageCount = imageCount;
    createInfo.imageFormat = chosenFormat.format;
    createInfo.imageColorSpace = chosenFormat.colorSpace;
    createInfo.imageExtent = extent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    if (indices.graphicsFamily != indices.presentFamily) {
        createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        createInfo.queueFamilyIndexCount = 2;
        createInfo.pQueueFamilyIndices = queueFamilyIndices;
    }
    else {
        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    }

    createInfo.preTransform = capabilities.currentTransform;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.presentMode = VK_PRESENT_MODE_FIFO_KHR;
    createInfo.clipped = VK_TRUE;
    createInfo.oldSwapchain = VK_NULL_HANDLE;

    std::cout << "Using format: " << chosenFormat.format
        << ", color space: " << chosenFormat.colorSpace << std::endl;
    std::cout << "Extent: " << extent.width << "x" << extent.height << std::endl;

    if (vkCreateSwapchainKHR(context.getDevice(), &createInfo, nullptr, &swapchain) != VK_SUCCESS) {
        throw std::runtime_error("failed to create swap chain");
    }

    // Obtener imágenes del swapchain
    uint32_t count;
    vkGetSwapchainImagesKHR(context.getDevice(), swapchain, &count, nullptr);
    images.resize(count);
    vkGetSwapchainImagesKHR(context.getDevice(), swapchain, &count, images.data());
}


void Swapchain::createImageViews(VulkanContext& context) {
    imageViews.resize(images.size());

    for (size_t i = 0; i < images.size(); i++) {
        VkImageViewCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        createInfo.image = images[i];
        createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        createInfo.format = format;
        createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        createInfo.subresourceRange.baseMipLevel = 0;
        createInfo.subresourceRange.levelCount = 1;
        createInfo.subresourceRange.baseArrayLayer = 0;
        createInfo.subresourceRange.layerCount = 1;

        if (vkCreateImageView(context.getDevice(), &createInfo, nullptr, &imageViews[i]) != VK_SUCCESS) {
            throw std::runtime_error("failed to create image views");
        }
    }
}

void Swapchain::createFramebuffers(VulkanContext& context, VkRenderPass renderPass) {
    framebuffers.resize(imageViews.size());

    for (size_t i = 0; i < imageViews.size(); i++) {
        VkImageView attachments[] = { imageViews[i] };

        VkFramebufferCreateInfo framebufferInfo{};
        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.renderPass = renderPass;  // ✅ ¡Este debe ser válido!
        framebufferInfo.attachmentCount = 1;
        framebufferInfo.pAttachments = attachments;
        framebufferInfo.width = extent.width;
        framebufferInfo.height = extent.height;
        framebufferInfo.layers = 1;

        if (vkCreateFramebuffer(context.getDevice(), &framebufferInfo, nullptr, &framebuffers[i]) != VK_SUCCESS) {
            throw std::runtime_error("failed to create framebuffer!");
        }
    }
}


void Swapchain::cleanupSwapchain(VulkanContext& context) {
    for (auto fb : framebuffers) {
        if (fb != VK_NULL_HANDLE) {
            vkDestroyFramebuffer(context.getDevice(), fb, nullptr);
        }
    }

    for (auto view : imageViews) {
        vkDestroyImageView(context.getDevice(), view, nullptr);
    }

    vkDestroySwapchainKHR(context.getDevice(), swapchain, nullptr);
}

VkExtent2D Swapchain::getExtent() const { return extent; }
VkFormat Swapchain::getFormat() const { return format; }
const std::vector<VkImageView>& Swapchain::getImageViews() const { return imageViews; }
const std::vector<VkFramebuffer>& Swapchain::getFramebuffers() const { return framebuffers; }



