#pragma once
#include <map>
// Global Mouse Getting Class, Don't set it by urself.
class Mouse
{
public:
	// Get by ref, if you want to get position.
	static void GetPosition(double& xpos, double& ypos);
	// Get by ref, if you want to get delta position.
	static void GetDeltaPosition(double& xdpos, double& ydpos);
	// Don't set it.
	static void SetPosition(double xpos, double ypos);
	// Get by ref, if you want to get wheel.
	static double GetDeltaWheel();
	// Don't set it.
	static void SetWheel(double xpos, double ypos);
	// 0 left 1 right 2 middle
	static bool GetButtonClick(int button);
	// 0 left 1 right 2 middle
	static bool GetButtonRelease(int button);
	// Don't set it.
	static void SetButton(int button, int action);
private:
	static bool initPos;
	static bool initWheel;
	static double globalPreXpos;
	static double globalPreYpos;
	static double globalXpos;
	static double globalYpos;
	static double globalWheel;
	static double wheelTimeStamp;
	static std::map<int, int> buttonStates;
};

