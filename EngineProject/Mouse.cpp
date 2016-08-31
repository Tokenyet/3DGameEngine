#include "Mouse.h"

void Mouse::GetPosition(double& xpos, double& ypos)
{
	xpos = globalXpos;
	ypos = globalYpos;
}
void Mouse::SetPosition(double xpos, double ypos)
{
	globalXpos = xpos;
	globalYpos = ypos;
}

// static member need to declare in cpp, or compile will report unsloved external symbol
double Mouse::globalXpos;
double Mouse::globalYpos;
