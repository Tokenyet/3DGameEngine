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
	LightSourceRenderer(CubeShader &shader);
	~LightSourceRenderer();
	void Prepare();
	void Render(Camera camera, Light entity);
private:
	CubeShader &shader;
	glm::mat4 projectionMatrix;
	const float FOV = 45.0f;
	const float NEAR_PLANE = 0.1f;
	const float FAR_PLANE = 500.0f;
};

