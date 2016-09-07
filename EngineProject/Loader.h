#pragma once
#include "Core.h"
#include "BasicRenderModel.h"
#include "Texture.h"

// Create Render Model by data
class Loader
{
public:
	Loader();
	~Loader();
	// Create Basic RenderModel by user data
	BasicRenderModel LoadRenderModel(float position[], int pdataLength);
	BasicRenderModel LoadRenderModel(float position[], int pdataLength, int indices[], int indexLength);
	BasicRenderModel LoadRenderModel(float position[], int pdataLength, int indices[], int indexLength, float texCoords[], int texCoordLength);
	BasicRenderModel LoadRenderModel(float position[], int pdataLength, int indices[], int indexLength, float texCoords[], int texCoordLength, float normals[], int normalLength);
	Texture LoadTexture(const char* path);
	void CleanUp();
private:
	// Create a empty vao object
	GLuint CreateVAO();
	void BindVAO(GLuint vao);
	void UnbindVAO();
	// Bind a vertex attribute on specific attribute number in vao,
	// Also create vbo to bind it.
	void BindVertexAttribute(int attributeNumber, int dimension, float data[], int dataLength);
	void BindIndices(int indices[], int indexLength);
	std::vector<GLuint>vaos;
	std::vector<GLuint>vbos;
	std::vector<GLuint>textures;
};

