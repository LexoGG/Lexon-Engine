#include "SceneMaster.h"

std::vector<StaticMesh> SceneMaster::SceneMesheslist;
std::vector<uint32_t> SceneMaster::selectedIndex;

void SceneMaster::AddMeshToList(StaticMesh mesh) {
	SceneMesheslist.push_back(mesh);
};

float SceneMaster::CameraPositionInit[3] = { 0.0f, 0.0f, 0.0f };


