#include "AnimatablePlayer.h"



AnimatablePlayer::AnimatablePlayer(MeshesModel model, glm::vec3 position, float rx, float ry, float rz, float scale)
	:Player(model, position, rx, ry, rz, scale)
{
	meshesModel = this->GetModel();
}

AnimatablePlayer::~AnimatablePlayer()
{
}

void AnimatablePlayer::PlayerMove(Terrain * terrain, float deltaTime)
{
	Player::PlayerMove(terrain, deltaTime);
	std::map<std::string, Animation*> animations = meshesModel->GetAnimations();
	ControlAnimation(animations);
}

void AnimatablePlayer::SetCurrentAnimation(std::string name)
{
	this->meshesModel->SetCurrentAnimation(name);
}


