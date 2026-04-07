#pragma once
#include <vulkan/vulkan.h>
#include "../Vulkan/VulkanContext.h"
#include "../Vulkan/UniformBuffer.h"
#include "../Core/Globals.h"
#include "../Assets/Textures.h"
#include <stdexcept>
# include <vector>
#include <iostream>

class Descriptors {

public:
	void createDescriptorPool();
	void createDescriptorSets();

	void destroyDescriptorPool();
	void destroyDescriptorSets();

	std::vector<VkDescriptorSet> getdescriptorsets() {

		return descriptorSets;
	}

	static VkDescriptorSet* getdescriptorsetsIndex(uint32_t indice) {

		return &descriptorSets[indice];
	}





private:
	VkDescriptorPool descriptorPool;
	static std::vector<VkDescriptorSet> descriptorSets;

};