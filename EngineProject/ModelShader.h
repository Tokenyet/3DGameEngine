#pragma once
#include "ShaderProgram.h"
#include "StaticShader.h"
#include "Light.h"

class ModelShader :
	public StaticShader
{
private:
	static const char * VERTEX_SHADER;
	static const char * FRAGMENT_SHADER;
protected:
	virtual void BindAttributes();
public:
	ModelShader();
	void SetDiffuse(GLuint texture);
	void SetSpecular(GLuint texture);
	void SetShininess(float shininess = 32.0f);
	void SetBoneTransform(int index, glm::mat4 transform);
	~ModelShader();
};

