#include "TerrainTexturePack.h"


TerrainTexturePack::TerrainTexturePack(Texture background, Texture rTexture, Texture gTexture, Texture bTexture)
{
	this->rTexture = rTexture;
	this->gTexture = gTexture;
	this->bTexture = bTexture;
	this->backgroundTexture = background;
}

Texture TerrainTexturePack::GetTextureBackground()
{
	return this->backgroundTexture;
}

Texture TerrainTexturePack::GetTextureRed()
{
	return this->rTexture;
}

Texture TerrainTexturePack::GetTextureGreen()
{
	return this->gTexture;
}

Texture TerrainTexturePack::GetTextureBlue()
{
	return this->bTexture;
}
