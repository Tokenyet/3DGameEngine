#pragma once
#include <map>
#include "BasicRenderModel.h"

class TextureModel
{
public:
	TextureModel();
	TextureModel(BasicRenderModel model, GLuint texture);
	BasicRenderModel GetBasicRenderModel();
	GLuint GetTextureID();
	// for map using
	bool operator<(TextureModel const& input) const
	{
		if (textureID < input.textureID)
			return true;
		else
			return false;
	}
private:
	BasicRenderModel model;
	GLuint textureID;
};

