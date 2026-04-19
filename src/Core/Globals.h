#pragma once

#include <vector>
#include <string>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

static const char *shadersdir = "shaders\\compileshaders.bat";

static const uint32_t WIDTH = 800*2;
static const uint32_t HEIGHT = 600*2;

static const int MAX_FRAMES_IN_FLIGHT = 2;

static const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

static const std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
};


static const std::string MODEL_PATH = "Objects/viking_room.obj";
static const std::string TEXTURE_PATH = "Objects/viking_room.png";

