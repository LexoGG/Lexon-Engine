

// StaticMesh.h
#include "../Vulkan/VulkanContext.h"
#include "../Vulkan/UniformBuffer.h"


class StaticMesh {
public:
    std::string changeName(std::string newname);

    std::string name;

    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 rotation = glm::vec3(0.0f);
    glm::vec3 scale = glm::vec3(1.0f);

    // Vulkan buffers
    VkBuffer vertexBuffer = VK_NULL_HANDLE;
    VkDeviceMemory vertexMemory = VK_NULL_HANDLE;
    VkBuffer indexBuffer = VK_NULL_HANDLE;
    VkDeviceMemory indexMemory = VK_NULL_HANDLE;

    uint32_t indexCount = 0;


};