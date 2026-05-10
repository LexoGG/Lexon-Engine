#pragma once

#include <vector>
#include <string>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

static const char *shadersdir = "shaders\\compileshaders.bat";

static const uint32_t WIDTH = uint32_t(1920.0f*1.0f);
static const uint32_t HEIGHT = uint32_t(1080.0f*1.0f);

static const int MAX_FRAMES_IN_FLIGHT = 2;

static const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

static const std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME,
    VK_KHR_SHADER_DRAW_PARAMETERS_EXTENSION_NAME,
    VK_KHR_DYNAMIC_RENDERING_EXTENSION_NAME
};

static const std::string MODEL_PATHC = "Objects/cubo.obj";

static const std::string MODEL_PATH = "Objects/viking_room.obj";
static const std::string TEXTURE_PATH = "Objects/viking_room.png";

struct {
    int Major = 0;
    int Minor = 0;
    int Patch = 0;
} m_instanceVersion;

