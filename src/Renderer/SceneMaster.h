#pragma once
#include <vector>
#include <memory>
#include <string>
#include "StaticMesh.h"


class SceneMaster {

public:
	static std::vector<StaticMesh> SceneMesheslist;
	static std::vector<uint32_t> selectedIndex;
	static float CameraPositionInit[3];
	static void AddMeshToList(StaticMesh mesh);
private:




};


