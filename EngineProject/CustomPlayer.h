#pragma once
#include "AnimatablePlayer.h"
class CustomPlayer :
	public AnimatablePlayer
{
public:
	CustomPlayer(MeshesModel model, glm::vec3 position, float rx, float ry, float rz, float scale);
	~CustomPlayer();
protected:
	virtual void ControlAnimation(std::map<std::string, Animation*> animations);
};

