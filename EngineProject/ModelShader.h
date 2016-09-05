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
public:
	ModelShader();
	void SetDiffuse(GLuint texture);
	void SetSpecular(GLuint texture);
	void SetShininess(float shininess = 32.0f);
	~ModelShader();
};

