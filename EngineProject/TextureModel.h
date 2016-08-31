#pragma once
#include "BasicRenderModel.h"
class TextureModel
{
public:
	TextureModel(BasicRenderModel model, GLuint texture);
	BasicRenderModel GetBasicRenderModel();
	GLuint GetTextureID();
private:
	BasicRenderModel model;
	GLuint textureID;
};

