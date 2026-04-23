#pragma once
#include <vector>
#include <memory>
#include <string>
#include "StaticMesh.h"


class SceneMaster {

public:
	static std::vector<StaticMesh> SceneMesheslist;

	static void AddMeshToList(StaticMesh mesh);

private:




};


