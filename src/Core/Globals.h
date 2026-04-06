#pragma once
#include <vector>

static const char *shadersdir = "shaders\\compileshaders.bat";

static const uint32_t WIDTH = 1920;
static const uint32_t HEIGHT = 1080;

static const int MAX_FRAMES_IN_FLIGHT = 2;

static const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

static const std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
};



