#pragma once
#include "PointLight.h"
class SpotLight :
	public PointLight
{
public:
	SpotLight(glm::vec3 position, BasicRenderModel model);
	~SpotLight();
};

