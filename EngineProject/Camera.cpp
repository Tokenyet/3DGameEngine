#include "Camera.h"

Camera::Camera(glm::vec3 pos)
{
	avoidInitCameraException = true;
	cameraPos = pos;
	glm::vec3 front;
	front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	front.y = sin(glm::radians(pitch));
	front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	cameraFront = glm::normalize(front);
	zoom = 45.0f;
}


Camera::~Camera()
{
}

void Camera::PlayerMove(float deltaTime)
{
	// Camera controls
	GLfloat cameraSpeed = 10.0f * deltaTime;
	if (Keyboard::GetKey(GLFW_KEY_W))
		cameraPos += cameraSpeed * cameraFront;
	if (Keyboard::GetKey(GLFW_KEY_S))
		cameraPos -= cameraSpeed * cameraFront;
	if (Keyboard::GetKey(GLFW_KEY_A))
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (Keyboard::GetKey(GLFW_KEY_D))
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	
	double mosX = 0, mosY = 0;
	Mouse::GetPosition(mosX, mosY);
	//if (mosX != lastX && mosY != lastY)
	MoveDirection(mosX, mosY);
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void Camera::ZoomVision(double yscroll)
{
	if (zoom >= 1.0f && zoom <= 45.0f)
		zoom -= yscroll*0.01;
	if (zoom <= 1.0f)
		zoom = 1.0f;
	if (zoom >= 45.0f)
		zoom = 45.0f;
}

void Camera::MoveDirection(double xpos, double ypos)
{
	if (avoidInitCameraException) // this bool variable is initially set to true
	{
		if (xpos == 0 && ypos == 0)
			return;
		lastX = (float)xpos;
		lastY = (float)ypos;
		avoidInitCameraException = false;
	}
	
	float xoffset = (float)xpos - lastX;
	float yoffset = lastY - (float)ypos; // Reversed since y-coordinates range from bottom to top
	lastX = (float)xpos;
	lastY = (float)ypos;

	GLfloat sensitivity = 0.05f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	front.y = sin(glm::radians(pitch));
	front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	cameraFront = glm::normalize(front);
}
