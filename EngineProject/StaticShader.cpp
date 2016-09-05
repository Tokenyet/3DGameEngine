#include "StaticShader.h"
const char * StaticShader::VERTEX_SHADER = "shader/basic.vert";
const char * StaticShader::FRAGMENT_SHADER = "shader/basic.frag";
StaticShader::StaticShader() : ShaderProgram(VERTEX_SHADER, FRAGMENT_SHADER)
{
	diffuseCount = 0;
	specularCount = 0;
	BindAttributes();
}

StaticShader::StaticShader(const char * vertex, const char * fragment)
	: ShaderProgram(vertex, fragment)
{
	diffuseCount = 0;
	specularCount = 0;
	BindAttributes();
}

void StaticShader::SetLight(Light light)
{
	int loc = GetUniformLocation("light.position");
	if (loc == -1) Debug::Log("Light Position Setting Fail.");
	glUniform3fv(loc, 1, glm::value_ptr(light.GetPosition()));
	loc = GetUniformLocation("light.ambient");
	if (loc == -1) Debug::Log("Light Ambient Setting Fail.");
	glUniform3fv(loc, 1, glm::value_ptr(light.GetAmbient()));
	loc = GetUniformLocation("light.diffuse");
	if (loc == -1) Debug::Log("Light Diffuse Setting Fail.");
	glUniform3fv(loc, 1, glm::value_ptr(light.GetDiffuse()));
	loc = GetUniformLocation("light.specular");
	if (loc == -1) Debug::Log("Light Specular Setting Fail.");
	glUniform3fv(loc, 1, glm::value_ptr(light.GetSpecular()));
}

StaticShader::~StaticShader()
{
	this->DeleteProgram();
}

void StaticShader::BindAttributes()
{
	BindAttribute(VertexAttributeLocationRule::position, "position");
	BindAttribute(VertexAttributeLocationRule::texCoord, "texCoord");
	BindAttribute(VertexAttributeLocationRule::normal, "normal");
}

GLuint StaticShader::GetUniformLocation(const char * name)
{
	return glGetUniformLocation(this->GetProgram(), name);
}

void StaticShader::SetDiffuse(GLuint texture)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	std::string diffuse = "diffuse";
	int loc = GetUniformLocation(diffuse.c_str());
	if (loc == -1) Debug::Log("Diffuse texture Setting Fail.");
	glUniform1i(loc, 0);
}

void StaticShader::SetSpecular(glm::vec3 materialSpecular)
{
	std::string specular = "specular";
	int loc = GetUniformLocation(specular.c_str());
	if (loc == -1) Debug::Log("Specular texture Setting Fail.");
	glUniform1i(loc, diffuseCount);
	diffuseCount++;
	specularCount++;
}

void StaticShader::SetShininess(float shininess)
{
	int loc = GetUniformLocation("shininess");
	if (loc == -1) Debug::Log("Material Shininess Setting Fail.");
	glUniform1f(loc, shininess);
}

void StaticShader::SetModelMatrix(glm::mat4 modelMatrix)
{
	int loc = GetUniformLocation("model");
	if (loc == -1) Debug::Log("Model Matrix Setting Fail.");
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
}

void StaticShader::SetViewPosition(glm::vec3 viewPosition)
{
	int loc = GetUniformLocation("viewPos");
	if (loc == -1) Debug::Log("View Position Setting Fail.");
	glUniform3fv(loc, 1, glm::value_ptr(viewPosition));
}

void StaticShader::SetViewMatrix(glm::mat4 viewMatrix)
{
	int loc = GetUniformLocation("view");
	if (loc == -1) Debug::Log("View Matrix Setting Fail.");
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
}

void StaticShader::SetProjectionMatrix(glm::mat4 projectionMatrix)
{
	int loc = GetUniformLocation("projection");
	if (loc == -1) Debug::Log("Projection Matrix Setting Fail.");
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
}

void StaticShader::ClearRelativeData()
{
	diffuseCount = 0;
	specularCount = 0;
}
