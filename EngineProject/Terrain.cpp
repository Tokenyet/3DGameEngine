#include "Terrain.h"

Terrain::Terrain(int gridX, int gridZ, Loader &loader, Texture blendMap, TerrainTexturePack pack) : loader(loader)
{
	this->blendMap = blendMap;
	this->x = gridX * SIZE;
	this->z = gridZ * SIZE;
	this->model = GenerateTerrian();
	this->terrainTexturePack = pack;
}

Texture Terrain::GetBlendMap()
{
	return this->blendMap;
}

TerrainTexturePack Terrain::GetTerrainTexturePack()
{
	return this->terrainTexturePack;
}

BasicRenderModel Terrain::GetModel()
{
	return this->model;
}

BasicRenderModel Terrain::GenerateTerrian()
{
	//glm::vec3 *vertices = new glm::vec3[width * height];
	GLfloat *vertices = new GLfloat[VERTEX_COUNT * VERTEX_COUNT * 3];
	GLfloat *texCoords = new GLfloat[VERTEX_COUNT * VERTEX_COUNT * 2];
	int texCoordLength = VERTEX_COUNT * VERTEX_COUNT * 2;
	GLfloat xstart = x;
	GLfloat xend = xstart + SIZE;
	GLfloat zstart = z;
	GLfloat zend = zstart + SIZE;
	// because x and z are 0~127, so cut distance to 127 steps.
	GLfloat xdis = (xend - xstart) / (GLfloat)(VERTEX_COUNT-1);
	GLfloat zdis = (zend - zstart) / (GLfloat)(VERTEX_COUNT-1);
	for (int i = 0; i < VERTEX_COUNT * VERTEX_COUNT; i++)
	{
		GLfloat xjump = (GLfloat)(i % VERTEX_COUNT);
		GLfloat zjump = (GLfloat)(i / VERTEX_COUNT);
		// float randNum = (float)(rand() % 10) / 100.0f;
		vertices[i * 3] = xstart + xdis * xjump;
		vertices[i * 3 + 1] = 0.0f;
		vertices[i * 3 + 2] = zstart + zdis * zjump;
		texCoords[i * 2] = xjump / (float)(VERTEX_COUNT-1);
		texCoords[i * 2 + 1] = zjump / (float)(VERTEX_COUNT-1);
		/*vertices[i] = glm::vec3(xstart + xdis * xjump,
		0.0f,
		zstart + zdis * zjump);*/
		//std::string x = std::to_string(vertices[i].x);
		//std::string y = std::to_string(vertices[i].y);
		//std::string z = std::to_string(vertices[i].z);
		//Debug::Log((x + "," + y + "," + z).c_str());
	}
	int * indices = GenerateTerrianIndices(VERTEX_COUNT, VERTEX_COUNT);
	vertices, GetVertexCount(), texCoords, indices, GetIndicesCount();
	return this->loader.LoadRenderModel(vertices, GetVertexCount(), indices, GetIndicesCount(), texCoords, texCoordLength);
}

int * Terrain::GenerateTerrianIndices(int widthPoint, int heightPoint)
{
	int *indices = new int[GetIndicesCount()];
	int index = 0;
	for (int i = 0; i < heightPoint - 1; i++)
	{
		int row = i * widthPoint;
		int nextRow = (i + 1) * widthPoint;
		for (int j = 0; j < widthPoint; j++)
		{
			indices[index] = row + j;
			indices[index + 1] = nextRow + j;
			index += 2;
		}
		if (i != heightPoint - 2)
		{
			indices[index] = indices[index - 1];
			indices[index + 1] = nextRow;
			index += 2;
		}
	}
	return indices;
}

int Terrain::GetIndicesCount()
{
	// width * 2 * (height - 1) + 2 *(height - 2)
	return VERTEX_COUNT * 2 * (VERTEX_COUNT - 1) + 2 * (VERTEX_COUNT - 2);
}

int Terrain::GetVertexCount()
{
	// width * height * 3
	return VERTEX_COUNT * VERTEX_COUNT * 3;
}