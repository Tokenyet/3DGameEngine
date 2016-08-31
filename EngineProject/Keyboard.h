#pragma once
// Global Keyboard Getting Class, Don't set it by urself.
class Keyboard
{
public:
	// Test with GLFW_KEY_{Any Key}
	static bool GetKey(int key);
	// Don't set it.
	static void SetKey(int key, bool state);
private:
	static bool keys[1024];
};

