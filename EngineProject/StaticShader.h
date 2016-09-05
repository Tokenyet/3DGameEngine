#pragma once
#include "ShaderProgram.h"
#include "Light.h"
class StaticShader :
	public ShaderProgram
{
private:
	static const char * VERTEX_SHADER;
	static const char * FRAGMENT_SHADER;
public:
	StaticShader();
	StaticShader(const char* vertex, const char* fragment);
	void SetLight(Light light);
	virtual void SetDiffuse(GLuint texture);
	virtual void SetSpecular(glm::vec3 materialSpecular);
	virtual void SetShininess(float shininess = 32.0f);
	void SetModelMatrix(glm::mat4 modelMatrix);
	void SetViewPosition(glm::vec3 viewPosition);
	void SetViewMatrix(glm::mat4 viewMatrix);
	void SetProjectionMatrix(glm::mat4 projectionMatrix);
	virtual void ClearRelativeData();
	~StaticShader();
protected:
	// set layout location for specific vertex attribute
	void BindAttributes();
	GLuint GetUniformLocation(const char* name);
	int diffuseCount;
	int specularCount;
};

