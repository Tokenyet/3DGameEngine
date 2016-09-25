#include "MeshModel.h"



MeshModel::MeshModel()
{
}

MeshModel::MeshModel(BasicRenderModel model, std::map<TextureType, std::vector<Texture>> textures)
{
	this->model = model;
	this->textures = textures;
}

BasicRenderModel MeshModel::GetBasicRenderModel()
{
	return this->model;
}

std::map<TextureType, std::vector<Texture>> MeshModel::GetTexutres()
{
	return this->textures;
}
