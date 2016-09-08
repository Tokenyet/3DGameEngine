#pragma once
#include "StaticShader.h"
#include "TerrainTexturePack.h"

class TerrainShader :
	public StaticShader
{
private:
	static const char * VERTEX_SHADER;
	static const char * FRAGMENT_SHADER;
public:
	TerrainShader();
	~TerrainShader();
	void SetBlendMap(GLuint blendMap);
	void SetTerrainTextures(TerrainTexturePack pack);
};

