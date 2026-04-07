// VulkanContext.h
#pragma once

#include "../Core/Window.h"
#include "../Core/Globals.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>
#include <optional>
#include <set>
#include <string>
#include <stdexcept>
#include <iostream>
#include <cstring>

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

class VulkanContext {
public:
    void createInstance();
    void init();
    void cleanup();

    static VkDevice getDevice() ;
    static VkInstance getInstance();
    static VkSurfaceKHR getSurface()  ;
    static VkSurfaceKHR* getSurfacePointer();

    static VkQueue getGraphicsQueue()  ;
    static VkQueue getPresentQueue()  ;

    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool isComplete() const {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
    static VkPhysicalDevice getPhysicalDevice() { return physicalDevice; };

    static SwapChainSupportDetails querySwapChainSupport (VkPhysicalDevice physicalDevice);


private:
    void setupDebugMessenger();
    void createSurface();
    void pickPhysicalDevice();
    void createLogicalDevice();

    bool checkValidationLayerSupport();
    std::vector<const char*> getRequiredExtensions();

    static VkDevice device;
    static VkInstance instance;
    static VkSurfaceKHR surface;
    static VkQueue graphicsQueue;
    static VkQueue presentQueue;

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
	bool isDeviceSuitable(VkPhysicalDevice device);
    bool checkDeviceExtensionSupport(VkPhysicalDevice device);
    void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

    VkDebugUtilsMessengerEXT debugMessenger;
    static VkPhysicalDevice physicalDevice;

};



