#pragma once
#ifndef CAMERA_H
#define CAMERA_H
#include "Core.h"
#include "DisplayManager.h"

class Camera
{
public:
	Camera(glm::vec3 pos);
	~Camera();
	// Move Camera in spectator mode.
	virtual void Move(float deltaTime);
	// Must need it.
	glm::mat4 GetViewMatrix();
	// For calculating specular
	glm::vec3 GetCameraPosition(){ return cameraPos; }
	// Some other using.
	glm::vec3 GetCameraFront() { return cameraFront; }
	// No using now.
	float GetCameraZoom() { return (float)zoom; }
protected:
	glm::vec3 cameraPos = glm::vec3(0.0f, 1.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(-1.0f, -0.5f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	float yaw = -90.0f;
	float pitch = -45.0f;
	double zoom;
private:
	// maybe need to remove this, bcz Mouse class is pretty now.
	bool avoidInitCameraException;
	float sensitivity = 0.05f;
	float lastX = 400, lastY = 300;
	//void MovePosition(bool keys[1024], GLfloat deltaTime);
	// get mouse xpos and ypos
	void MoveDirection(double xpos, double ypos);
};

#endif

