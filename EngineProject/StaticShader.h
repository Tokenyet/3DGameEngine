#pragma once
#include "ShaderProgram.h"
class StaticShader :
	public ShaderProgram
{
private:
	static const char * VERTEX_SHADER;
	static const char * FRAGMENT_SHADER;
public:
	StaticShader();
	void SetDiffuseTexture(GLuint texture);
	virtual void ClearRelativeData();
	~StaticShader();
protected:
	// set layout location for specific vertex attribute
	void BindAttributes();
	GLuint GetUniformLocation(const char* name);
	int diffuseCount;
};

