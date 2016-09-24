#pragma once
#include "Core.h"
#include "DisplayManager.h"
#include "Camera.h"
#include "Player.h"

template <class T>
class PlayerCamera : public Camera
{
public:
	// The template of player camera isn't care, but need to give it as player's template type.
	PlayerCamera(Player<T> &player): Camera(glm::vec3(0, 0, 0)) ,player(player)
	{
		pitch = 20.0f;
		yaw = 0.0f;
	}

	// Move Camera Around Player
	void Move(float deltaTime) 
	{
		float zoom = (float)Mouse::GetDeltaWheel() * 0.5f;
		if (Keyboard::GetKey(GLFW_KEY_LEFT_SHIFT))
			zoom *= 0.2f;
		distanceFromPlayer -= zoom;
		MovePitch();
		MoveYaw();
		float heightDistance = distanceFromPlayer * glm::sin(glm::radians(pitch));
		float widthDistance = distanceFromPlayer * glm::cos(glm::radians(pitch));
		float theta = player.GetRotationY();
		float xDistance = widthDistance * glm::sin(glm::radians(theta + yaw));
		float zDistance = widthDistance * glm::cos(glm::radians(theta + yaw));
		glm::vec3 playerPosition = player.GetPosition();
		cameraPos = playerPosition + glm::vec3(-xDistance, heightDistance, -zDistance);
		cameraFront = glm::normalize(playerPosition - cameraPos);
	}
private:
	float distanceFromPlayer = 20.0f;
	Player<T> &player;
	// Up and down using left button.
	void MovePitch();
	// Left and right using right button.
	void MoveYaw();
};

template<class T>
void PlayerCamera<T>::MovePitch()
{
	if (Mouse::GetButtonClick(0))
	{
		double mx, my;
		Mouse::GetDeltaPosition(mx, my);
		pitch -= (float)my * 0.1f;
	}
}

template<class T>
void PlayerCamera<T>::MoveYaw()
{
	if (Mouse::GetButtonClick(1))
	{
		double mx, my;
		Mouse::GetDeltaPosition(mx, my);
		yaw -= (float)mx * 0.1f;
	}
}
