#include "Time.h"


double Time::GetNowTime()
{
	return currentTime;
}

void Time::Update()
{
	previousTime = currentTime;
	currentTime = glfwGetTime();
	deltaTime = currentTime - previousTime;
}

double Time::GetDeltaTime()
{
	return deltaTime;
}

double Time::currentTime = 0;
double Time::previousTime = 0;
double Time::deltaTime = 0;
