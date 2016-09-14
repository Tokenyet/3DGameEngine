#pragma once
#include "Terrain.h"
#include "Entity.h"
template< class T>
class Player :
	public Entity<T>
{
public:
	Player() {}
	Player(T model, glm::vec3 position, float rx, float ry, float rz, float scale);
	void PlayerMove(Terrain* terrain, float deltaTime);
private:
	const float RUN_SPEED = 5.0f;
	const float TURN_SPEED = 160.0f;
	const float GRAVITY = -50.0f;
	const float JUMP_POWER = 10.0f;
	float currentSpeed;
	float currentTurnSpeed;
	float jumpSpeed;
	bool airState;
	void CheckUserInputs();
	void Jump();

};

template<class T>
Player<T>::Player(T model, glm::vec3 position, float rx, float ry, float rz, float scale)
	:Entity<T>(model, position, rx, ry, rz, scale) {}

template<class T>
void Player<T>::PlayerMove(Terrain* terrain, float deltaTime)
{
	CheckUserInputs();
	float distance = currentSpeed * deltaTime;
	float dx = distance * glm::sin(glm::radians(this->GetRotationY()));
	float dz = distance * glm::cos(glm::radians(this->GetRotationY()));
	this->MovePosition(dx, 0.0f, dz);
	this->MoveRotation(0.0f, currentTurnSpeed * deltaTime, 0.0f);	
	this->jumpSpeed += GRAVITY * deltaTime;
	this->MovePosition(0.0f, this->jumpSpeed * deltaTime, 0.0f);
	float terrainHeight = terrain->GetHeightByPosition(this->GetPosition().x, this->GetPosition().z);
	if (this->GetPosition().y < terrainHeight)
	{
		this->MovePosition(0.0f, terrainHeight - this->GetPosition().y, 0.0f);
		airState = false;
	}
}

template<class T>
void Player<T>::CheckUserInputs()
{
	if (Keyboard::GetKey(GLFW_KEY_W))
		this->currentSpeed = RUN_SPEED;
	else if (Keyboard::GetKey(GLFW_KEY_S))
		this->currentSpeed = -RUN_SPEED;
	else
		this->currentSpeed = 0;

	if (Keyboard::GetKey(GLFW_KEY_A))
		this->currentTurnSpeed = TURN_SPEED;
	else if (Keyboard::GetKey(GLFW_KEY_D))
		this->currentTurnSpeed = -TURN_SPEED;
	else
		this->currentTurnSpeed = 0;

	if (Keyboard::GetKey(GLFW_KEY_SPACE))
		Jump();
}

template<class T>
void Player<T>::Jump()
{
	if (!airState)
	{
		this->jumpSpeed = JUMP_POWER;
		airState = true;
	}
}
