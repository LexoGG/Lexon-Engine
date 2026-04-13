#pragma once

#include <vulkan/vulkan.h>
#include "../Assets/Textures.h"

class DepthBuffer {
public:

    static void createDepthResources();

    static VkImage getdepthImage() { return depthImage; };
    static VkDeviceMemory getdepthImageMemory() { return depthImageMemory; };
    static VkImageView getdepthImageView() { return depthImageView; };

    static VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
    static VkFormat findDepthFormat();
    bool hasStencilComponent(VkFormat format);

private:
    static VkImage depthImage;
    static VkDeviceMemory depthImageMemory;
    static VkImageView depthImageView;
};

