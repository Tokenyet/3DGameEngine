#pragma once
#include "ShaderProgram.h"
#include "Light.h"

class CubeShader :
	public ShaderProgram
{
private:
	static const char * VERTEX_SHADER;
	static const char * FRAGMENT_SHADER;
public:
	CubeShader();
	void SetLight(Light light);
	void SetModelMatrix(glm::mat4 modelMatrix);
	void SetViewMatrix(glm::mat4 viewMatrix);
	void SetProjectionMatrix(glm::mat4 projectionMatrix);
	~CubeShader();
protected:
	// set layout location for specific vertex attribute
	void BindAttributes();
	GLuint GetUniformLocation(const char* name);
};

