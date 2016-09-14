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

#include <chrono>

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

	static void StartMeasureNumber(int number)
	{
		if (measurements.find(number) == measurements.end())
			measurements.insert(std::pair<int, std::chrono::time_point<std::chrono::steady_clock>>(number, std::chrono::high_resolution_clock::now()));
		measurements[number] = std::chrono::high_resolution_clock::now();
	}

	static void EndMeasureNumber(int number)
	{
		if (measurements.find(number) == measurements.end())
		{
			Debug::Log("No Start Time");
			return;
		}
		std::chrono::time_point<std::chrono::steady_clock> end = std::chrono::high_resolution_clock::now();
		long long timer = std::chrono::duration_cast<std::chrono::milliseconds>(end - measurements[number]).count();
		Debug::Log(std::to_string(timer) + "ms");
	}
private:
	static std::map<int, std::chrono::time_point<std::chrono::steady_clock>> measurements;
};

// Manage Vertex Attribute Location
enum VertexAttributeLocationRule
{
	position = 0,
	texCoord = 1,
	normal = 2,
};


// Any platform need to hook Core's callback to using static Keyboard and Mouse classes.
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

	// Set by Display Manager, because Display Manager has window.
	static void MouseWheelCallback(GLFWwindow* window, double xoffset, double yoffset)
	{
		Mouse::SetWheel(xoffset, yoffset);
	}

	// Set by Display Manager, because Display Manager has window.
	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		Mouse::SetButton(button, action);
	}
};


class CustomMath 
{
public:
	static void Barycentric(glm::vec2 p, glm::vec2 a, glm::vec2 b, glm::vec2 c, float &u, float &v, float &w)
	{
		glm::vec2 v0 = b - a;
		glm::vec2 v1 = c - a;
		glm::vec2 v2 = p - a;
		float d00 = glm::dot(v0, v0);
		float d01 = glm::dot(v0, v1);
		float d11 = glm::dot(v1, v1);
		float d20 = glm::dot(v2, v0);
		float d21 = glm::dot(v2, v1);
		float invDenom = 1.0f / (d00 * d11 - d01 * d01);
		v = (d11 * d20 - d01 * d21) * invDenom;
		w = (d00 * d21 - d01 * d20) * invDenom;
		u = 1.0f - v - w;
	}
};
#endif