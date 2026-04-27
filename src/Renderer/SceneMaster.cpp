#include "SceneMaster.h"

std::vector<StaticMesh> SceneMaster::SceneMesheslist;

void SceneMaster::AddMeshToList(StaticMesh mesh) {
	SceneMesheslist.push_back(mesh);
};

float SceneMaster::CameraPositionInit[3] = { 0.0f, 0.0f, 0.0f };