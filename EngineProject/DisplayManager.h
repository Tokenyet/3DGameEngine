#ifndef  DISPLAY_MANAGER_H
#define  DISPLAY_MANAGER_H
#pragma once
#include "Core.h"
class DisplayManager
{
public:
	// Call it before loop
	static void CreateDisplay();
	// Call it at loop end
	static void UpdateDisplay();
	// Call it when application close before.
	static void CloseDisplay();
	// Check closable
	static bool IsCloseRequested();

	static int GetWindowWidth() { return WIDTH; }
	
	static int GetWindowHeight() { return HEIGHT; }

	static float GetDeltaTime() { return deltaTime; }
private:
	// init glfw any parameter
	static void InitGLFW();
	// init glew any parameter
	static void InitGLEW();
	// window width
	static const int WIDTH = 1280;
	// window height
	static const int HEIGHT = 720;
	//static const int FPS_LIMIT = 120;
	static GLFWwindow *window;
	static float deltaTime;
	static float previousTime;
};
#endif // ! DISPLAY_MANAGER_H

