#pragma once
#include "Texture.h"
class TerrainTexturePack
{
public:
	TerrainTexturePack() {}
	TerrainTexturePack(Texture background, Texture rTexture, Texture gTexture, Texture bTexture);
	Texture GetTextureBackground();
	Texture GetTextureRed();
	Texture GetTextureGreen();
	Texture GetTextureBlue ();
private:
	Texture backgroundTexture;
	Texture rTexture;
	Texture gTexture;
	Texture bTexture;
};

