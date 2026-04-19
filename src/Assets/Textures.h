#pragma once

#include <stdexcept>
#include "../Vulkan/BufferUtils.h"
#include "../Vulkan/VulkanContext.h"
#include <iostream>


#include <filesystem>   // a��delo arriba con los dem�s includes


class Textures {

public:
    void createTextureImage();

    void createTextureImageView();
    void createTextureSampler();
    void generateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels);
	static VkImageView getTextureImageView() {		return textureImageView;	}

	static VkSampler getTextureSampler() {	return textureSampler;	}
    static uint32_t getMipLevels() { return mipLevels; }

    static VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels);
    static void createImage(uint32_t width, uint32_t height, uint32_t mipLevels, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
    void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, uint32_t mipLevels);
    void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

private:


    VkImage textureImage;
    VkDeviceMemory textureImageMemory;
    static VkImageView textureImageView;
    static VkSampler textureSampler;
    static uint32_t mipLevels;
};



