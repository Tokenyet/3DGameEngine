#pragma once
#include <map>
#include "BasicRenderModel.h"
#include "Texture.h"


class TextureModel
{
public:
	TextureModel();
	TextureModel(BasicRenderModel model, Texture texture);
	BasicRenderModel GetBasicRenderModel();
	GLuint GetTextureID();
	// for map using
	bool operator<(TextureModel const& input) const
	{
		if (texture < input.texture)
			return true;
		else
			return false;
	}
private:
	BasicRenderModel model;
	Texture texture;
};

