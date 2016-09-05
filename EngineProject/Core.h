 #pragma once
#ifndef CORE_H
#define CORE_H
#include <Windows.h>
// GLEW ( help you using functions without retreiving functions )
#define GLEW_STATIC
#include <GL\glew.h>
// GLFW ( make you a windows that support opengl operation to work fine with your platform )
#include <GLFW\glfw3.h>
// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// list
#include <vector>
#include <string>
// SOIL
#include <SOIL2.h>
// basic
#include "Mouse.h"
#include "Keyboard.h"

// Ouput Any Message to visual studio output window
class Debug 
{
public:
	static void Log(const char* string) 
	{
		OutputDebugString(string);
		OutputDebugString("\n");
	}
	static void Log(std::string str)
	{
		OutputDebugString(str.c_str());
		OutputDebugString("\n");
	}
};


// Manage Vertex Attribute Location
enum VertexAttributeLocationRule
{
	position = 0,
	texCoord = 1,
	normal = 2,
};

class Core 
{
public:
	// Set by Display Manager, because Display Manager has window.
	static void KeyboardCallback(GLFWwindow * window, int key, int scancode, int action, int mods)
	{
		if (action == GLFW_PRESS)
			Keyboard::SetKey(key, true);
		else if (action == GLFW_RELEASE)
			Keyboard::SetKey(key, false);
	}

	// Set by Display Manager, because callback forks all call by DM.
	static void ErrorCallback(int error, const char * description)
	{
		std::string errorString = "Error code:" + std::to_string(error) + "," + description;
		Debug::Log(errorString);
	}

	// Set by Display Manager, because Display Manager has window.
	static void MouseCallback(GLFWwindow* window, double xpos, double ypos)
	{
		Mouse::SetPosition(xpos, ypos);
	}
};
#endif