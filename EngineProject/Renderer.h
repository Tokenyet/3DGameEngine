#pragma once
#include "Core.h"
#include "BasicRenderModel.h"
class Renderer
{
public:
	Renderer();
	~Renderer();
	void Prepare();
	void Render(BasicRenderModel model);
};

