#pragma once
#include "Light.h"
class PointLight :
	public Light
{
public:
	PointLight(glm::vec3 position, BasicRenderModel model);
	void SetPointLightParameter(float constant = 1.0f, float linear = 0.09f, float quadratic = 0.032f);
	float GetConstant() { return this->constant; }
	float GetLinear() { return this->linear; }
	float GetQuadratic() { return this->quadratic; }
	~PointLight();
private:
	float constant;
	float linear;
	float quadratic;
};

