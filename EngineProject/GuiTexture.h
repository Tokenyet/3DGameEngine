#pragma once
#include "Core.h"

class GuiTexture
{
public:
	GuiTexture(Texture texture, glm::vec2 position, float rotation, glm::vec2 scale)
	{
		this->texture = texture;
		this->position = position;
		this->scale = scale;
		this->rotation = rotation;
	}
	float GetRotation() { return rotation; }
	glm::vec2 GetPosition() { return position; }
	glm::vec2 GetScale() { return scale; }
	Texture GetTexture() { return texture; }
private:
	Texture texture;
	glm::vec2 position;
	glm::vec2 scale;
	float rotation;

};