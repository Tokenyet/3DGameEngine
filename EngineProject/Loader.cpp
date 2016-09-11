#include "Loader.h"



Loader::Loader()
{
}


Loader::~Loader()
{
}

BasicRenderModel Loader::LoadRenderModel(float position[], int pdataLength)
{
	GLuint vaoID = CreateVAO();
	BindVAO(vaoID);
	BindVertexAttribute(VertexAttributeLocationRule::position, 3, position, pdataLength);
	UnbindVAO();
	return BasicRenderModel(vaoID, pdataLength);
}

BasicRenderModel Loader::LoadRenderModel(float position[], int pdataLength, int indices[], int indexLength)
{
	GLuint vaoID = CreateVAO();
	BindVAO(vaoID);
	BindVertexAttribute(VertexAttributeLocationRule::position, 3, position, pdataLength);
	BindIndices(indices, indexLength);
	UnbindVAO();
	return BasicRenderModel(vaoID, indexLength);
}

BasicRenderModel Loader::LoadRenderModel(float position[], int pdataLength, int indices[], int indexLength, float texCoords[], int texCoordLength)
{
	GLuint vaoID = CreateVAO();
	BindVAO(vaoID);
	BindVertexAttribute(VertexAttributeLocationRule::position, 3, position, pdataLength);
	BindVertexAttribute(VertexAttributeLocationRule::texCoord, 2, texCoords, texCoordLength);
	BindIndices(indices, indexLength);
	UnbindVAO();
	return BasicRenderModel(vaoID, indexLength);
}

BasicRenderModel Loader::LoadRenderModel(float position[], int pdataLength, int indices[], int indexLength, float texCoords[], int texCoordLength, float normals[], int normalLength)
{
	GLuint vaoID = CreateVAO();
	BindVAO(vaoID);
	BindVertexAttribute(VertexAttributeLocationRule::position, 3, position, pdataLength);
	BindVertexAttribute(VertexAttributeLocationRule::texCoord, 2, texCoords, texCoordLength);
	BindVertexAttribute(VertexAttributeLocationRule::normal, 3, normals, normalLength);
	BindIndices(indices, indexLength);
	UnbindVAO();
	return BasicRenderModel(vaoID, indexLength);
}

Texture Loader::LoadTexture(const char * path)
{
	GLuint texture;
	glGenTextures(1, &texture);
	textures.push_back(texture);
	glBindTexture(GL_TEXTURE_2D, texture); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
										   // Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, 0);
	// Load, create texture and generate mipmaps
	int width, height;
	unsigned char* image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	//return Texture(texture, width, height);
	return Texture(texture);
}

// remember to call SOIL_free_image_data to free the image
unsigned char* Loader::LoadCustomImage(const char * path, int &width, int &height, int soilformat)
{
	unsigned char* image = SOIL_load_image(path, &width, &height, 0, soilformat);
	//return Texture(texture, width, height);
	return image;
}

void Loader::CleanUp()
{
	for each (GLuint vao in vaos)
		glDeleteVertexArrays(1, &vao);
	for each (GLuint vbo in vbos)
		glDeleteBuffers(1, &vbo);
	for each (GLuint texture in textures)
		glDeleteTextures(1, &texture);
}

GLuint Loader::CreateVAO()
{
	GLuint vao;
	glGenVertexArrays(1, &vao);
	vaos.push_back(vao);
	return vao;
}

void Loader::BindVAO(GLuint vao)
{
	glBindVertexArray(vao);
}

void Loader::UnbindVAO()
{
	glBindVertexArray(0);
}

void Loader::BindVertexAttribute(int attributeNumber, int dimension, float data[], int dataLength)
{
	GLuint vboID;
	vbos.push_back(vboID);
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, dataLength * sizeof(float), data, GL_STATIC_DRAW);
	glVertexAttribPointer(attributeNumber, dimension, GL_FLOAT, GL_FALSE, dimension * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(attributeNumber);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::BindIndices(int indices[], int indexLength)
{
	GLuint ebo;
	glGenBuffers(1, &ebo);
	vbos.push_back(ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexLength * sizeof(int), indices, GL_STATIC_DRAW);
}
