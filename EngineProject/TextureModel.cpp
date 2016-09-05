#include "TextureModel.h"


TextureModel::TextureModel()
{
}

TextureModel::TextureModel(BasicRenderModel model, GLuint texture)
{
	this->model = model;
	this->textureID = texture;
}

BasicRenderModel TextureModel::GetBasicRenderModel()
{
	return this->model;
}

GLuint TextureModel::GetTextureID()
{
	return this->textureID;
}
