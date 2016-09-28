#pragma once
#include "Core.h"
#include "Loader.h"
#include "GuiTexture.h"
#include "GuiShader.h"

class GuiRenderer
{
public:
	GuiRenderer();
	~GuiRenderer();
	void Render(std::vector<GuiTexture> textures);
	float* CalculateInitPosition(int width, int height);
private:
	//BasicRenderModel quad;
	GLuint vbo;
	GLuint vao;
	GuiShader shader;
};

