#pragma once
#include "Core.h"
#include "BasicRenderModel.h"

class Light
{
public:
	Light(glm::vec3 position, BasicRenderModel model);
	void SetColorParameter(glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f)
		, float ambient = 0.2f, float diffuse = 0.5f, float specular = 1.0f);
	glm::vec3 GetPosition();
	glm::vec3 GetColor();
	glm::vec3 GetAmbient();
	glm::vec3 GetDiffuse();
	glm::vec3 GetSpecular();
	BasicRenderModel GetModel();
private:
	glm::vec3 position;
	glm::vec3 color;
	float ambient, diffuse, specular;
	BasicRenderModel model;
};

