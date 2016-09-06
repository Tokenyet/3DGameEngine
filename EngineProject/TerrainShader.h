#pragma once
#include "StaticShader.h"
class TerrainShader :
	public StaticShader
{
private:
	static const char * VERTEX_SHADER;
	static const char * FRAGMENT_SHADER;
public:
	TerrainShader();
	~TerrainShader();
};

