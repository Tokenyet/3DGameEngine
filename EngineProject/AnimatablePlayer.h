#pragma once
#include "Core.h"
#include "Player.h"
#include "MeshesModel.h"

class AnimatablePlayer :
	public Player<MeshesModel>
{
public:
	AnimatablePlayer(MeshesModel model, glm::vec3 position, float rx, float ry, float rz, float scale);
	~AnimatablePlayer();
	// override, just want to hook the ControlAnimation.
	void PlayerMove(Terrain* terrain, float deltaTime);
protected:
	void SetCurrentAnimation(std::string);
	virtual void ControlAnimation(std::map<std::string, Animation*> animations) = 0;
private:
	MeshesModel *meshesModel;
};

