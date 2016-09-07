#include "TextureModel.h"


TextureModel::TextureModel()
{
}

TextureModel::TextureModel(BasicRenderModel model, Texture texture)
{
	this->model = model;
	this->texture = texture;
}

BasicRenderModel TextureModel::GetBasicRenderModel()
{
	return this->model;
}

Texture TextureModel::GetTexture()
{
	return this->texture;
}
