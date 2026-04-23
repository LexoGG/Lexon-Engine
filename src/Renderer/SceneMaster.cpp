#include "SceneMaster.h"

std::vector<StaticMesh> SceneMaster::SceneMesheslist;

void SceneMaster::AddMeshToList(StaticMesh mesh) {
	SceneMesheslist.push_back(mesh);
};
