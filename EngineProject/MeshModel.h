#pragma once
#include "BasicRenderModel.h"
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
	MeshModel(BasicRenderModel model, std::map<TextureType, std::vector<GLuint>> textures);
	BasicRenderModel GetBasicRenderModel();
	std::map<TextureType, std::vector<GLuint>> GetTexutres();
private:
	BasicRenderModel model;
	std::map<TextureType, std::vector<GLuint>> textures;
};

