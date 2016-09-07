#include "Light.h"


Light::Light(glm::vec3 position, BasicRenderModel model)
{
	this->position = position;
	this->model = model;
	SetColorParameter();
}

void Light::SetColorParameter(glm::vec3 color, float ambient, float diffuse, float specular)
{
	this->color = color;
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
}

void Light::MovePosition(float x, float y, float z)
{
	this->position += glm::vec3(x, y, z);
}

glm::vec3 Light::GetPosition()
{
	return position;
}

glm::vec3 Light::GetColor()
{
	return this->color;
}

glm::vec3 Light::GetAmbient()
{
	return this->color * this->ambient;
}

glm::vec3 Light::GetDiffuse()
{
	return this->color * this->diffuse;
}

glm::vec3 Light::GetSpecular()
{
	return this->color * this->specular;
}

BasicRenderModel Light::GetModel()
{
	return model;
}
