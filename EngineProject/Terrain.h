#pragma once
#include "Core.h"
#include "BasicRenderModel.h"
#include "Texture.h"
#include "TerrainTexturePack.h"
#include "Loader.h"

class Terrain
{
public:
	Terrain(int gridX, int gridZ, Loader &loader, Texture blendMap, TerrainTexturePack pack);
	Texture GetBlendMap();
	TerrainTexturePack GetTerrainTexturePack();
	BasicRenderModel GetModel();
	glm::vec3 GetPosition() { return glm::vec3(0, 0, 0); }
private:
	const float SIZE = 800.0f;
	const int VERTEX_COUNT = 128;
	float x;
	float z;
	BasicRenderModel model;
	Texture blendMap;
	TerrainTexturePack terrainTexturePack;
	Loader &loader;
	BasicRenderModel GenerateTerrian();
	int GetIndicesCount();
	int GetVertexCount();
	int *GenerateTerrianIndices(int widthPoint, int heightPoint);
};

