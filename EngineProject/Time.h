#pragma once
#ifndef TIME_H
#define TIME_H
#include "Core.h"

class Time
{
public:
	static void Update();
	static double GetNowTime();
	static double GetDeltaTime();
private:
	static double previousTime;
	static double currentTime;
	static double deltaTime;
};

#endif
