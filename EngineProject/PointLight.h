#pragma once
#include "Light.h"
class PointLight :
	public Light
{
public:
	PointLight(glm::vec3 position, BasicRenderModel model);
	~PointLight();
};

