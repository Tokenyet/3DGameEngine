#include "CubeShader.h"

const char * CubeShader::VERTEX_SHADER = "shader/lightSource.vert";
const char * CubeShader::FRAGMENT_SHADER = "shader/lightSource.frag";
CubeShader::CubeShader() : ShaderProgram(VERTEX_SHADER, FRAGMENT_SHADER)
{
	BindAttributes();
}

void CubeShader::SetLight(Light light)
{
	int loc = GetUniformLocation("lightColor");
	if (loc == -1) Debug::Log("Light Color Setting Fail.");
	glUniform3fv(loc, 1, glm::value_ptr(light.GetColor()));
}

CubeShader::~CubeShader()
{
	this->DeleteProgram();
}

void CubeShader::BindAttributes()
{
	BindAttribute(VertexAttributeLocationRule::position, "position");
}

GLuint CubeShader::GetUniformLocation(const char * name)
{
	return glGetUniformLocation(this->GetProgram(), name);
}

void CubeShader::SetModelMatrix(glm::mat4 modelMatrix)
{
	int loc = GetUniformLocation("model");
	if (loc == -1) Debug::Log("Model Matrix Setting Fail.");
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
}

void CubeShader::SetViewMatrix(glm::mat4 viewMatrix)
{
	int loc = GetUniformLocation("view");
	if (loc == -1) Debug::Log("View Matrix Setting Fail.");
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
}

void CubeShader::SetProjectionMatrix(glm::mat4 projectionMatrix)
{
	int loc = GetUniformLocation("projection");
	if (loc == -1) Debug::Log("Projection Matrix Setting Fail.");
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
}
