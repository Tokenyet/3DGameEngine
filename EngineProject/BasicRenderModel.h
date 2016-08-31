#pragma once
#include "Core.h"
// Basic Render DataModel
class BasicRenderModel
{
public:
	BasicRenderModel();
	BasicRenderModel(GLuint vaoID, int vertexCount);
	~BasicRenderModel();
	GLuint GetVaoID();
	int GetVertexCount();
private:
	GLuint vaoID;
	int vertexCount;
};

