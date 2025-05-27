// VulkanContext.h
#pragma once

#include "../Core/Window.h"
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>
#include <optional>
#include <set>
#include <string>

class VulkanContext {
public:
    void init(Window& window);
    void cleanup(Window& window);

    VkDevice getDevice() const;
    VkInstance getInstance() const;
    VkSurfaceKHR getSurface() const;
    VkQueue getGraphicsQueue() const;
    VkQueue getPresentQueue() const;

public:
    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool isComplete() const {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
    VkPhysicalDevice getPhysicalDevice() const { return physicalDevice; }


private:
    void createInstance();
    void setupDebugMessenger();
    void createSurface(Window& window);
    void pickPhysicalDevice();
    void createLogicalDevice();

    bool checkValidationLayerSupport();
    std::vector<const char*> getRequiredExtensions();

    VkInstance instance = VK_NULL_HANDLE;
    VkDebugUtilsMessengerEXT debugMessenger;
    VkSurfaceKHR surface;

    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device = VK_NULL_HANDLE;
    VkQueue graphicsQueue;
    VkQueue presentQueue;


    const std::vector<const char*> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };

#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif
};
