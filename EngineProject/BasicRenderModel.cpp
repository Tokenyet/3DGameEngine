#include "BasicRenderModel.h"



BasicRenderModel::BasicRenderModel()
{
}

BasicRenderModel::BasicRenderModel(GLuint vaoID, int vertexCount)
{
	this->vaoID = vaoID;
	this->vertexCount = vertexCount;
}


BasicRenderModel::~BasicRenderModel()
{
}

GLuint BasicRenderModel::GetVaoID()
{
	return this->vaoID;
}

int BasicRenderModel::GetVertexCount()
{
	return this->vertexCount;
}
