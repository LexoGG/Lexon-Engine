#include "SceneMaster.h"

std::vector<StaticMesh> SceneMaster::SceneMesheslist;
std::vector<UniformBufferObject> SceneMaster::UniformObjectslist;

void SceneMaster::AddMeshToList(StaticMesh mesh) {
	SceneMesheslist.push_back(mesh);
};

float SceneMaster::CameraPositionInit[3] = { 0.0f, 0.0f, 0.0f };

int SceneMaster::selectedMeshIndex=0;   // ← selección global
