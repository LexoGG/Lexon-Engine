#pragma once
#include "StaticMesh.h"

StaticMesh::StaticMesh() {
    position[0] = position[1] = position[2] = 0.0f;
    rotation[0] = rotation[1] = rotation[2] = 0.0f;
    scale[0] = scale[1] = scale[2] = 1.0f;
    name = "Mesh";
}


std::string StaticMesh::changeName(std::string newname) {

	return name = newname;
}

void StaticMesh::getModelMatrix(glm::mat4 &model) {




    glm::vec3 objectPositionvec = glm::vec3(position[0] / 100, position[1] / 100, position[2] / 100);
    glm::vec3 objectScalevec = glm::vec3(scale[0], scale[1], scale[2]);

    //movimiento
    glm::mat4 modeltr = glm::translate(glm::mat4(1.0f), objectPositionvec);   // ← traslación primero
    //rotacion
    glm::mat4 modelx = glm::rotate(glm::mat4(1.0f), glm::radians(rotation[0]), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 modely = glm::rotate(glm::mat4(1.0f), glm::radians(rotation[1]), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 modelz = glm::rotate(glm::mat4(1.0f), glm::radians(rotation[2]), glm::vec3(0.0f, 0.0f, 1.0f));
    //escalado
    glm::mat4 modelscale = glm::scale(glm::mat4(1.0f), objectScalevec);

    model = modeltr * modelx * modely * modelz * modelscale;


}

void StaticMesh::Draw(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout) {
    if (indexCount == 0 || vertexBuffer == VK_NULL_HANDLE || indexBuffer == VK_NULL_HANDLE) {
        return;
    }

    // Bind buffers PROPIOS de este mesh
    VkBuffer vertexBuffers[] = { vertexBuffer };
    VkDeviceSize offsets[] = { 0 };
    vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);
    vkCmdBindIndexBuffer(commandBuffer, indexBuffer, 0, VK_INDEX_TYPE_UINT32);

    // Transform propio
    glm::mat4 model;
    getModelMatrix(model);
    vkCmdPushConstants(commandBuffer, pipelineLayout,
        VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(glm::mat4), &model);

    vkCmdDrawIndexed(commandBuffer, indexCount, 1, 0, 0, 0);
}



std::unordered_map<Vertex, uint32_t> StaticMesh::DataMesh;


void StaticMesh::createBuffers(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices) {
    if (vertices.empty() || indices.empty()) return;

    VkDeviceSize vertSize = sizeof(Vertex) * vertices.size();
    VkDeviceSize indSize = sizeof(uint32_t) * indices.size();

    // Vertex buffer (igual que VertexBuffer.cpp pero por mesh)
    VkBuffer stagingVert;
    VkDeviceMemory stagingVertMem;
    BufferUtils::createBuffer(vertSize,
        VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        stagingVert, stagingVertMem);

    void* data;
    vkMapMemory(VulkanContext::getDevice(), stagingVertMem, 0, vertSize, 0, &data);
    memcpy(data, vertices.data(), static_cast<size_t>(vertSize));
    vkUnmapMemory(VulkanContext::getDevice(), stagingVertMem);

    BufferUtils::createBuffer(vertSize,
        VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
        vertexBuffer, vertexMemory);

    BufferUtils::copyBuffer(stagingVert, vertexBuffer, vertSize);

    vkDestroyBuffer(VulkanContext::getDevice(), stagingVert, nullptr);
    vkFreeMemory(VulkanContext::getDevice(), stagingVertMem, nullptr);

    // Index buffer (igual que IndexBuffer.cpp pero por mesh)
    VkBuffer stagingInd;
    VkDeviceMemory stagingIndMem;
    BufferUtils::createBuffer(indSize,
        VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        stagingInd, stagingIndMem);

    vkMapMemory(VulkanContext::getDevice(), stagingIndMem, 0, indSize, 0, &data);
    memcpy(data, indices.data(), static_cast<size_t>(indSize));
    vkUnmapMemory(VulkanContext::getDevice(), stagingIndMem);

    BufferUtils::createBuffer(indSize,
        VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
        indexBuffer, indexMemory);

    BufferUtils::copyBuffer(stagingInd, indexBuffer, indSize);

    vkDestroyBuffer(VulkanContext::getDevice(), stagingInd, nullptr);
    vkFreeMemory(VulkanContext::getDevice(), stagingIndMem, nullptr);

    std::cout << "[StaticMesh] Buffers creados para " << name << std::endl;
}