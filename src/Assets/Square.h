#pragma once

#include "../Core/Globals.h"
#include "../Vulkan/Vertex.h"
#include <stdexcept>


class LoaderModels {
public:
    void loadModel(std::string newname, std::string MODEL_PATH);
        static std::vector<Vertex> vertices;
    static std::vector<uint32_t> indices;

private:

};





