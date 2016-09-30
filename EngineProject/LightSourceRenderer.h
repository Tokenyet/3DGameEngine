#pragma once
#include "Core.h"
#include "DisplayManager.h"
#include "BasicRenderModel.h"
#include "CubeShader.h"
#include "Entity.h"
#include "Camera.h"


class LightSourceRenderer
{
public:
	LightSourceRenderer(CubeShader &shader, glm::mat4 projectionMatrix);
	~LightSourceRenderer();
	void Render(Camera camera, std::vector<Light*> lights);
private:
	CubeShader &shader;
	glm::mat4 projectionMatrix;
};

