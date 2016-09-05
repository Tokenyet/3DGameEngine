#pragma once
#include "MeshModel.h"
class MeshesModel
{
public:
	MeshesModel();
	MeshesModel(std::vector<MeshModel> meshes);
	std::vector<MeshModel> GetMeshes() { return this->meshes; }
private:
	std::vector<MeshModel> meshes;
};

