#include "Terrain.h"

Terrain::Terrain(int gridX, int gridZ, Loader &loader, Texture blendMap, TerrainTexturePack pack, std::string heightMap) : loader(loader)
{
	this->blendMap = blendMap;
	this->x = gridX * SIZE;
	this->z = gridZ * SIZE;
	this->heightMap = heightMap;
	if (heightMap != "")
	{
		int width, height;
		int format = SOIL_LOAD_RGB;
		unsigned char *pixels = loader.LoadCustomImage(heightMap.c_str(), width, height, format);
		this->model = GenerateTerrian(width, height, pixels);
		SOIL_free_image_data(pixels);
	}
	else
		this->model = GenerateTerrian();
	this->terrainTexturePack = pack;
}

Terrain::~Terrain()
{
	if(heightsOfTerrian != nullptr)
		delete heightsOfTerrian;
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

float Terrain::GetHeightByPosition(float testX, float testZ)
{
	float xInTerrain = testX - this->x;
	float zInTerrain = testZ - this->z;
	float gridWidth = SIZE / (this->widthVertexCount - 1);
	float gridHeight = SIZE / (this->heightVertexCount - 1);
	int gridX = (int)glm::floor(xInTerrain / gridWidth);
	int gridZ = (int)glm::floor(zInTerrain / gridHeight);
	if (gridX > this->widthVertexCount - 1 || gridZ > this->heightVertexCount - 1 || gridX < 0 || gridZ < 0)
		return 0;
	float xCoord = (xInTerrain - (int)(xInTerrain / gridWidth) * gridWidth) / gridWidth;
	float zCoord = (zInTerrain - (int)(zInTerrain / gridHeight) * gridHeight) / gridHeight;
	float u, v, w, answer;
	glm::vec3 topLeft = glm::vec3(0, heightsOfTerrian[gridX + gridZ * widthVertexCount], 0);
	glm::vec3 topRight = glm::vec3(1, heightsOfTerrian[gridX + 1 + gridZ * widthVertexCount], 0);
	glm::vec3 bottomLeft = glm::vec3(0, heightsOfTerrian[gridX + (gridZ + 1) * widthVertexCount], 1);
	glm::vec3 bottomRight = glm::vec3(1, heightsOfTerrian[gridX + 1 + (gridZ + 1) * widthVertexCount], 1);
	if (xCoord < 1.0 - zCoord)
	{
		CustomMath::Barycentric(glm::vec2(xCoord, zCoord), glm::vec2(topLeft.x, topLeft.z), glm::vec2(topRight.x, topRight.z), glm::vec2(bottomLeft.x, bottomRight.z), u, v, w);
		answer = topLeft.y * u + topRight.y * v + bottomLeft.y * w;
	}
	else
	{
		CustomMath::Barycentric(glm::vec2(xCoord, zCoord), glm::vec2(topRight.x, topRight.z), glm::vec2(bottomLeft.x, bottomLeft.z), glm::vec2(bottomRight.x, bottomRight.z), u, v, w);
		answer = topRight.y * u + bottomLeft.y * v + bottomRight.y * w;
	}
	return answer;
}

BasicRenderModel Terrain::GenerateTerrian(int width, int height, unsigned char* pixels)
{
	this->widthVertexCount = width;
	this->heightVertexCount = height;
	GLfloat *vertices = new GLfloat[width * height * 3];
	GLfloat *texCoords = new GLfloat[width * height * 2];
	GLfloat *normals = new GLfloat[width * height * 3];
	int texCoordLength = width * height * 2;
	GLfloat xstart = x;
	GLfloat xend = xstart + SIZE;
	GLfloat zstart = z;
	GLfloat zend = zstart + SIZE;
	// because x and z are 0~127, so cut distance to 127 steps.
	GLfloat xdis = (xend - xstart) / (GLfloat)(width - 1);
	GLfloat zdis = (zend - zstart) / (GLfloat)(height - 1);
	heightsOfTerrian = new float[width * height];
	for (int i = 0; i < width * height; i++)
	{
		GLfloat xjump = (GLfloat)(i % width);
		GLfloat zjump = (GLfloat)(i / width);
		vertices[i * 3] = xstart + xdis * xjump;
		if (pixels != nullptr)
			vertices[i * 3 + 1] = (GLfloat)GetHeight((int)xjump, (int)zjump, pixels, SOIL_LOAD_RGB, width, height);
		else
			vertices[i * 3 + 1] = 0.0f;
		heightsOfTerrian[i] = vertices[i * 3 + 1];
		vertices[i * 3 + 2] = zstart + zdis * zjump;
		if (pixels != nullptr)
		{
			glm::vec3 normal = GetNormal((int)xjump, (int)zjump, pixels, SOIL_LOAD_RGB, width, height);
			normals[i * 3] = normal.x;
			normals[i * 3 + 1] = normal.y;
			normals[i * 3 + 2] = normal.z;
		}
		else
		{
			normals[i * 3] = 0.0f;
			normals[i * 3 + 1] = 1.0f;
			normals[i * 3 + 2] = 0.0f;
		}
		texCoords[i * 2] = xjump / (float)(width - 1);
		texCoords[i * 2 + 1] = zjump / (float)(height - 1);
	}
	int * indices = GenerateTerrianIndices(width, height);
	//vertices, GetVertexCount(VERTEX_COUNT, VERTEX_COUNT), texCoords, indices, GetIndicesCount(VERTEX_COUNT, VERTEX_COUNT);
	return this->loader.LoadRenderModel(vertices, GetVertexCount(width, height),
		indices, GetIndicesCount(width, height),
		texCoords, texCoordLength,
		normals, GetVertexCount(width, height));
}

/*
BasicRenderModel Terrain::GenerateTerrian()
{
	int width, height;
	int format = SOIL_LOAD_RGB;
	unsigned char *pixels = loader.LoadCustomImage("images/heightmap.png", width, height, format);
	int VERTEX_COUNT = height;
	GLfloat *vertices = new GLfloat[VERTEX_COUNT * VERTEX_COUNT * 3];
	GLfloat *texCoords = new GLfloat[VERTEX_COUNT * VERTEX_COUNT * 2];
	GLfloat *normals = new GLfloat[VERTEX_COUNT * VERTEX_COUNT * 3];
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
		vertices[i * 3] = xstart + xdis * xjump;
		vertices[i * 3 + 1] = (GLfloat)GetHeight((int)xjump, (int)zjump, pixels, format, width, height);
		vertices[i * 3 + 2] = zstart + zdis * zjump;
		glm::vec3 normal = GetNormal((int)xjump, (int)zjump, pixels, format, width, height);
		normals[i * 3] = normal.x;
		normals[i * 3 + 1] = normal.y;
		normals[i * 3 + 2] = normal.z;
		texCoords[i * 2] = xjump / (float)(VERTEX_COUNT-1);
		texCoords[i * 2 + 1] = zjump / (float)(VERTEX_COUNT-1);
	}
	int * indices = GenerateTerrianIndices(VERTEX_COUNT, VERTEX_COUNT);
	SOIL_free_image_data(pixels);
	//vertices, GetVertexCount(VERTEX_COUNT, VERTEX_COUNT), texCoords, indices, GetIndicesCount(VERTEX_COUNT, VERTEX_COUNT);
	return this->loader.LoadRenderModel(vertices, GetVertexCount(VERTEX_COUNT, VERTEX_COUNT),
		indices, GetIndicesCount(VERTEX_COUNT, VERTEX_COUNT),
		texCoords, texCoordLength,
		normals, GetVertexCount(VERTEX_COUNT, VERTEX_COUNT));
}*/

int * Terrain::GenerateTerrianIndices(int widthPoint, int heightPoint)
{
	int *indices = new int[GetIndicesCount(widthPoint, heightPoint)];
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

int Terrain::GetIndicesCount(int widthVertex, int heightVertex)
{
	// width * 2 * (height - 1) + 2 *(height - 2)
	return widthVertex * 2 * (heightVertex - 1) + 2 * (heightVertex - 2);
}

int Terrain::GetVertexCount(int widthVertex, int heightVertex)
{
	// width * height * 3
	return widthVertex * heightVertex * 3;
}

float Terrain::GetHeight(int x, int z, unsigned char* pixels, int channels, int width, int height)
{
	if (z < 0 || x < 0)
		return 0.0f;
	unsigned char r = pixels[z * width * channels + x];
	unsigned char g = pixels[z * width * channels + x + 1];
	unsigned char b = pixels[z * width * channels + x + 2];
	int value = r << 16 | g << 8 | b ;
	float currentPixel = (float)value;
	currentPixel -= MAXIMUM_PIXEL_COUNT / 2.0f;
	currentPixel /= MAXIMUM_PIXEL_COUNT / 2.0f;
	currentPixel *= MAX_HEIGHT;
	return currentPixel;
}

glm::vec3 Terrain::GetNormal(int x, int z, unsigned char* bits, int channels, int width, int height)
{
	float heightLeft =  GetHeight(x - 1, z, bits, channels, width, height);
	float heightRight = GetHeight(x + 1, z, bits, channels, width, height);
	float heightDown = GetHeight(x, z - 1, bits, channels, width, height);
	float heightUp = GetHeight(x, z + 1, bits, channels, width, height);

	// left point at -x, right point at +x, down point at -z, up point at +z
	// if left height > right height, feedback unsigned to +x correspond to normal imagination.
	// if down height > up height, feedback unsigned to +z correspond to normal imagination.
	// 2.0 because in tangent space up is 1.0 and this algorithm use finite difference by degree 2.
	return glm::normalize(glm::vec3(heightLeft - heightRight, 2.0f, heightDown - heightUp));
}