#pragma once
#include "../Vulkan/Vertex.h"
#include <vector>
#include <iostream>

static void ImpulsoejeY(glm::vec3 &vector, float mov) {
	float vectorpos_x = vector[0];
	float vectorpos_y = vector[1];
	float vectorpos_z = vector[2];

	float newvectorpos_x = vectorpos_x;
	float newvectorpos_y = vectorpos_y;
	float mewvectorpos_z = vectorpos_z + mov;
};

static float TamanoVector(glm::vec3 vector) {
	return std::sqrt(vector[0] * vector[0] + vector[1] * vector[1] + vector[2] * vector[2]);

};