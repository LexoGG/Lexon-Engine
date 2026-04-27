

// StaticMesh.h
#include "../Vulkan/VulkanContext.h"
#include "../Vulkan/UniformBuffer.h"


class StaticMesh {
public:
    StaticMesh();
    void Draw(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout);

    std::string changeName(std::string newname);
     void getModelMatrix(glm::mat4 &model);
     
     std::string name;
     float position[3];
     float rotation[3];
     float scale[3];

    std::vector<VkBuffer> uniformBuffers;
    std::vector<VkDeviceMemory> uniformBuffersMemory;
    std::vector<void*> uniformBuffersMapped;

    // Descriptor sets for this object (one per frame in flight)
    std::vector<VkDescriptorSet> descriptorSets;

    // Vulkan buffers
    VkBuffer vertexBuffer = VK_NULL_HANDLE;
    VkDeviceMemory vertexMemory = VK_NULL_HANDLE;
    VkBuffer indexBuffer = VK_NULL_HANDLE;
    VkDeviceMemory indexMemory = VK_NULL_HANDLE;

    static std::unordered_map<Vertex, uint32_t> DataMesh;

    VkDescriptorSet descriptorsets;
    uint32_t indexCount = 0;


};