#pragma once
// Global Mouse Getting Class, Don't set it by urself.
class Mouse
{
public:
	// Get by ref, if you want to get position.
	static void GetPosition(double& xpos, double& ypos);
	// Don't set it.
	static void SetPosition(double xpos, double ypos);
private:
	static double globalXpos;
	static double globalYpos;
};

