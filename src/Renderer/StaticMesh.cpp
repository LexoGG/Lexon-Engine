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
    if (indexCount == 0) return;

    // Usamos los buffers globales (mismo modelo para todos)
    VkBuffer vertexBuffers[] = { VertexBuffer::getBuffer() };
    VkDeviceSize offsets[] = { 0 };
    vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);
    vkCmdBindIndexBuffer(commandBuffer, IndexBuffer::getIndexVertexCount(), 0, VK_INDEX_TYPE_UINT32);

    glm::mat4 model;
    getModelMatrix(model);
    vkCmdPushConstants(commandBuffer, pipelineLayout,
        VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(glm::mat4), &model);

    vkCmdDrawIndexed(commandBuffer, indexCount, 1, 0, 0, 0);
}


std::unordered_map<Vertex, uint32_t> StaticMesh::DataMesh;
