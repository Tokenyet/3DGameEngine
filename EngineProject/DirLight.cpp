#include "DirLight.h"



DirLight::DirLight(glm::vec3 position, BasicRenderModel model, glm::vec3 lightDirection) :Light(position, model)
{
	this->lightDir = lightDirection;
	this->lightType = LightType::DirLightType;
}


DirLight::~DirLight()
{
}

glm::vec3 DirLight::GetLightDir()
{
	/*float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 2.0f - 1.0f;
	float y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 2.0f - 1.0f;
	float z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 2.0f - 1.0f;
	return glm::vec3(x, y, z);*/
	return this->lightDir;
}
