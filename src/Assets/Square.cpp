//Siempre en el cpp se incluye el h
#include "Square.h"
#include "../Renderer/SceneMaster.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

void LoaderModels::loadModel(std::string newname, std::string MODEL_PATH) {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string err, warn;

    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, MODEL_PATH.c_str())) {
        throw std::runtime_error(err);
    }

    StaticMesh mesh;
    mesh.changeName(newname);
    SceneMaster::AddMeshToList(mesh);

    std::unordered_map<Vertex, uint32_t> uniqueVertices{};

    LoaderModels::vertices.clear();   // ← importante: limpia lo anterior
    LoaderModels::indices.clear();

    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices) {
            Vertex vertex{};

            vertex.pos = {
                attrib.vertices[3 * index.vertex_index + 0],
                attrib.vertices[3 * index.vertex_index + 1],
                attrib.vertices[3 * index.vertex_index + 2]
            };

            vertex.texCoord = {
                attrib.texcoords[2 * index.texcoord_index + 0],
                1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
            };

            vertex.color = { 1.0f, 1.0f, 1.0f };

            if (uniqueVertices.count(vertex) == 0) {
                uniqueVertices[vertex] = static_cast<uint32_t>(LoaderModels::vertices.size());
                LoaderModels::vertices.push_back(vertex);
            }

            LoaderModels::indices.push_back(uniqueVertices[vertex]);
        }
    }

    // Actualizar el indexCount del último mesh añadido (el que acabamos de crear)
    if (!SceneMaster::SceneMesheslist.empty()) {
        SceneMaster::SceneMesheslist.back().indexCount = static_cast<uint32_t>(LoaderModels::indices.size());
    }
}



std::vector<Vertex> LoaderModels::vertices;
std::vector<uint32_t> LoaderModels::indices;