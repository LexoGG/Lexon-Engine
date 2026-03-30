#pragma once

#include "../Vulkan/Vertex.h"
#include <iostream>
#include <vector>
#include <stdexcept>
#include <chrono>

class Cuadrado {
    public:
         std::vector<Vertex> createsquare(float lado);
         std::vector<uint32_t> GetIndex();
    private:
        float lado = 0.0f;
};