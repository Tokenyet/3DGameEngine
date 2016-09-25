#include "CustomPlayer.h"



CustomPlayer::CustomPlayer(MeshesModel model, glm::vec3 position, float rx, float ry, float rz, float scale)
	:AnimatablePlayer(model, position, rx, ry, rz, scale)
{
}

CustomPlayer::~CustomPlayer()
{
}

void CustomPlayer::ControlAnimation(std::map<std::string, Animation*> animations)
{
	if (Keyboard::GetKey(GLFW_KEY_W) || Keyboard::GetKey(GLFW_KEY_S)
		|| Keyboard::GetKey(GLFW_KEY_A) || Keyboard::GetKey(GLFW_KEY_D))
		this->SetCurrentAnimation("Walk");
	else
		this->SetCurrentAnimation("Idle");
}
