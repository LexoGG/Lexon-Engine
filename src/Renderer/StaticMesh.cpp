#pragma once
#include "StaticMesh.h"


std::string StaticMesh::changeName(std::string newname) {

	return name = newname;
}

void StaticMesh::getModelMatrix(glm::mat4 &model) {




    glm::vec3 objectPositionvec = glm::vec3(position[0] / 100, position[1] / 100, position[2] / 100);
    glm::vec3 objectScalevec = glm::vec3(scale[0], scale[1], scale[2]);


    //rotacion
    glm::mat4 modelx = glm::rotate(glm::mat4(1.0f), glm::radians(rotation[0]), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 modely = glm::rotate(glm::mat4(1.0f), glm::radians(rotation[1]), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 modelz = glm::rotate(glm::mat4(1.0f), glm::radians(rotation[2]), glm::vec3(0.0f, 0.0f, 1.0f));

    //movimiento
    glm::mat4 modeltr = glm::translate(glm::mat4(1.0f), objectPositionvec);   // ← traslación primero

    //escalado
    glm::mat4 modelscale = glm::scale(glm::mat4(1.0f), objectScalevec);
    model = modeltr * modelx * modely * modelz * modelscale;


}

float StaticMesh::position[3] = { 0.0f, 0.0f, 0.0f };
float StaticMesh::rotation[3] = { 0.0f, 0.0f, 0.0f };
float StaticMesh::scale[3] = { 1.0f, 1.0f, 1.0f };
std::unordered_map<Vertex, uint32_t> StaticMesh::DataMesh;
