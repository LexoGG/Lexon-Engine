#pragma once

#include "../Core/Globals.h"
#include "../Vulkan/Vertex.h"
#include <stdexcept>


class LoaderModels {
public:
    static void loadModel(std::string name, std::string MODEL_PATH);
    static std::vector<Vertex> vertices;
    static std::vector<uint32_t> indices;

private:

};





