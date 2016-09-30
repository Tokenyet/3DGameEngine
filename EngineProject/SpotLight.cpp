#include "SpotLight.h"



SpotLight::SpotLight(glm::vec3 position, BasicRenderModel model) :PointLight(position, model)
{
	this->lightType = LightType::SpotLightType;
}



SpotLight::~SpotLight()
{
}
