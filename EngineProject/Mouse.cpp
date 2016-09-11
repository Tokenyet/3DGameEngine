#include "Mouse.h"
#include "Core.h"

void Mouse::GetPosition(double& xpos, double& ypos)
{
	xpos = globalXpos;
	ypos = globalYpos;
}

void Mouse::GetDeltaPosition(double & xdpos, double & ydpos)
{
	xdpos = globalXpos - globalPreXpos;
	ydpos = globalYpos - globalPreYpos;		
	if (!initPos)
		xdpos = ydpos = 0;
}

void Mouse::SetPosition(double xpos, double ypos)
{
	globalPreXpos = globalXpos;
	globalPreYpos = globalYpos;
	globalXpos = xpos;
	globalYpos = ypos;
	if (!initPos)
		if (globalPreXpos && globalPreYpos)
			initPos = true;
}

double Mouse::GetDeltaWheel()
{
	if (glfwGetTime() - wheelTimeStamp > 0.2)
		return 0;
	return globalWheel;
}

void Mouse::SetWheel(double xpos, double ypos)
{
	wheelTimeStamp = glfwGetTime();
	globalWheel = ypos;
}

bool Mouse::GetButtonClick(int button)
{
	if (buttonStates.find(button) != buttonStates.end())
		return buttonStates[button] == GLFW_PRESS;
	return false;
}

bool Mouse::GetButtonRelease(int button)
{
	if (buttonStates.find(button) != buttonStates.end())
		return buttonStates[button] == GLFW_RELEASE;
	return false;
}

void Mouse::SetButton(int button, int action)
{
	if (buttonStates.find(button) == buttonStates.end())
		buttonStates.insert(std::pair<int, int>(button, action));
	else
		buttonStates[button] = action;
}

// static member need to declare in cpp, or compile will report unsloved external symbol
bool Mouse::initPos = false;
double Mouse::globalPreXpos = 0;
double Mouse::globalPreYpos = 0;
double Mouse::globalXpos = 0;
double Mouse::globalYpos = 0;
double Mouse::globalWheel = 0;
double Mouse::wheelTimeStamp = 0;
std::map<int, int> Mouse::buttonStates;