#include "PointLight.h"



PointLight::PointLight(glm::vec3 position, BasicRenderModel model):Light(position, model)
{
	this->lightType = LightType::PointLightType;
}


PointLight::~PointLight()
{
}
