#include "PointLight.h"



PointLight::PointLight(glm::vec3 position, BasicRenderModel model):Light(position, model)
{
	this->lightType = LightType::PointLightType;
	SetPointLightParameter();
}

void PointLight::SetPointLightParameter(float constant, float linear, float quadratic)
{
	this->constant = constant;
	this->linear = linear;
	this->quadratic = quadratic;
}


PointLight::~PointLight()
{
}
