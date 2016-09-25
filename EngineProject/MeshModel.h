#pragma once
#include "BasicRenderModel.h"
#include "Texture.h"
#include <map>

enum TextureType {
	diffuse,
	specular,
	normaltexture,
};

class MeshModel
{
public:
	MeshModel();
	MeshModel(BasicRenderModel model, std::map<TextureType, std::vector<Texture>> textures);
	BasicRenderModel GetBasicRenderModel();
	std::map<TextureType, std::vector<Texture>> GetTexutres();
private:
	BasicRenderModel model;
	std::map<TextureType, std::vector<Texture>> textures;
};

