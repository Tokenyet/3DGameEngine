#pragma once
#include "Core.h"
#include "BasicRenderModel.h"
#include "TerrainShader.h"
#include "Terrain.h"
#include "Camera.h"

class TerrainRenderer
{
public:
	TerrainRenderer(TerrainShader &shader, glm::mat4 projectionMatrix);
	~TerrainRenderer();
	void Render(std::vector<Terrain> terrians);
private:
	TerrainShader &shader;
	glm::mat4 projectionMatrix;
	void PrepareTextureModel(Texture texture);
	void UnbindTextureModel();
	void PrepareInstance(Terrain terrain);
};


