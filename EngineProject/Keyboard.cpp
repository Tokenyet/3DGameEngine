#include "Keyboard.h"

bool Keyboard::GetKey(int key)
{
	if (key > 1023 || key < 0)
		return false;
	return keys[key];
}
void Keyboard::SetKey(int key, bool state)
{
	keys[key] = state;
}

// static member need to declare in cpp, or compile will report unsloved external symbol
bool Keyboard::keys[1024];
