#include "StaticShader.h"
const char * StaticShader::VERTEX_SHADER = "shader/basic.vert";
const char * StaticShader::FRAGMENT_SHADER = "shader/basic.frag";
StaticShader::StaticShader() : ShaderProgram(VERTEX_SHADER, FRAGMENT_SHADER)
{
	diffuseCount = 0;
	BindAttributes();
}


StaticShader::~StaticShader()
{
	this->DeleteProgram();
}

void StaticShader::BindAttributes()
{
	BindAttribute(VertexAttributeLocationRule::position, "position");
	BindAttribute(VertexAttributeLocationRule::texCoord, "texCoord");
}

GLuint StaticShader::GetUniformLocation(const char * name)
{
	return glGetUniformLocation(this->GetProgram(), name);
}

void StaticShader::SetDiffuseTexture(GLuint texture)
{
	glActiveTexture(GL_TEXTURE0 + diffuseCount);
	glBindTexture(GL_TEXTURE_2D, texture);
	std::string diffuse = "diffuse" + std::to_string(diffuseCount);
	int loc = GetUniformLocation(diffuse.c_str());
	if (loc == -1) Debug::Log("Diffuse texture Setting Fail.");
	glUniform1i(loc, diffuseCount);
	diffuseCount++;
}

void StaticShader::ClearRelativeData()
{
	diffuseCount = 0;
}
