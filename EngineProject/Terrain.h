#pragma once
#include "Core.h"
#include "BasicRenderModel.h"
#include "Texture.h"
#include "TerrainTexturePack.h"
#include "Loader.h"
#include <bitset>

class Terrain
{
public:
	Terrain(int gridX, int gridZ, Loader &loader, Texture blendMap, TerrainTexturePack pack, std::string heightMap = "");
	~Terrain();
	Texture GetBlendMap();
	TerrainTexturePack GetTerrainTexturePack();
	BasicRenderModel GetModel();
	float GetHeightByPosition(float testX, float testZ);
	glm::vec3 GetPosition() { return glm::vec3(0, 0, 0); }
private:
	const float SIZE = 800.0f;
	//const int VERTEX_COUNT = 128;
	const float MAX_HEIGHT = 40.0f;
	const int MAXIMUM_PIXEL_COUNT = 256 * 256 * 256;
	int widthVertexCount;
	int heightVertexCount;
	float x;
	float z;
	float *heightsOfTerrian;
	std::string heightMap;
	BasicRenderModel model;
	Texture blendMap;
	TerrainTexturePack terrainTexturePack;
	Loader &loader;
	//BasicRenderModel GenerateTerrian();
	BasicRenderModel GenerateTerrian(int width = 128 , int height = 128 , unsigned char* pixels = nullptr);
	int GetIndicesCount(int width, int height);
	int GetVertexCount(int width, int height);
	int *GenerateTerrianIndices(int widthPoint, int heightPoint);
	float GetHeight(int x, int z, unsigned char* bits, int channels, int width, int height);
	glm::vec3 GetNormal(int x, int z, unsigned char* bits, int channels, int width, int height);
};
