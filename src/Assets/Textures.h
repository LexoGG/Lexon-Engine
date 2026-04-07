#pragma once

#include <stdexcept>
#include "../Vulkan/BufferUtils.h"
#include "../Vulkan/VulkanContext.h"
#include <iostream>


class Textures {

public:
    void createTextureImage();

    void createTextureImageView();
    void createTextureSampler();

	static VkImageView getTextureImageView() {		return textureImageView;	}

	static VkSampler getTextureSampler() {	return textureSampler;	}

    static VkImageView createImageView(VkImage image, VkFormat format);
    void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
    void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
    void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

private:


    VkImage textureImage;
    VkDeviceMemory textureImageMemory;
    static VkImageView textureImageView;
    static VkSampler textureSampler;
};



