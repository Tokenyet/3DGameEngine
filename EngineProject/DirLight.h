#pragma once
#include "Light.h"
class DirLight :
	public Light
{
public:
	DirLight(glm::vec3 position, BasicRenderModel model, glm::vec3 lightDirection);
	~DirLight();
	glm::vec3 GetLightDir();
private:
	glm::vec3 lightDir;
};

