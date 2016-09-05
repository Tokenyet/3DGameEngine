#include "DisplayManager.h"



void DisplayManager::CreateDisplay()
{
	InitGLFW();
	InitGLEW();
	// Define the viewport dimensions (if you will change the winodw size, put these in loop)
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	previousTime = deltaTime = 0.0f;
}

void DisplayManager::UpdateDisplay()
{
	float currentTime = (float)glfwGetTime();
	deltaTime = currentTime - previousTime;
	previousTime = currentTime;
	glfwSwapBuffers(window); // show on windows
	glfwPollEvents(); // polling keyboard,mouse...event.
}

void DisplayManager::CloseDisplay()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

bool DisplayManager::IsCloseRequested()
{
	if (Keyboard::GetKey(GLFW_KEY_ESCAPE))
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	return glfwWindowShouldClose(window) > 0 ? true : false;
}
	
void DisplayManager::InitGLFW()
{
	// Init and Check GLFW working properly
	int glfwInitCheck = glfwInit();
	if (glfwInitCheck == GLFW_FALSE)
	{
		//std::cout << "glfw initilization failed." << std::endl;
		Debug::Log("glfw initilization failed.");
		//return -1;
	}

	// Create GLFW windows for requirement version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	window = glfwCreateWindow(WIDTH, HEIGHT, "Engine Project", NULL, NULL);
	if (window == nullptr) // window creation failed
	{
		//return -1;
	}
	glfwMakeContextCurrent(window);  // set current windows to interact with opengl api 

	// Set GLFW callback functions
	glfwSetErrorCallback(Core::ErrorCallback); // hook to core.h
	glfwSetKeyCallback(window, Core::KeyboardCallback);
	glfwSetCursorPosCallback(window, Core::MouseCallback);
	// Options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void DisplayManager::InitGLEW()
{
	// According to source code, this make you to access successfully full extension from some latest driver without error.
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (glewInit() != GLEW_OK)
	{
		Debug::Log("Failed to initialize GLEW");
		//std::cout << "Failed to initialize GLEW" << std::endl;
		//return -1;
	}
}

// static member need to declare in cpp, or compile will report unsloved external symbol
GLFWwindow* DisplayManager::window;
float DisplayManager::deltaTime;
float DisplayManager::previousTime;
