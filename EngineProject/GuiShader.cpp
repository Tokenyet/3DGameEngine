#include "GuiShader.h"

const char * GuiShader::VERTEX_SHADER = "shader/gui.vert";
const char * GuiShader::FRAGMENT_SHADER = "shader/gui.frag";

GuiShader::GuiShader() : ShaderProgram(VERTEX_SHADER, FRAGMENT_SHADER)
{}

GuiShader::GuiShader(const char * vertex, const char * fragment)
	: ShaderProgram(vertex, fragment)
{}

GuiShader::~GuiShader()
{
}

void GuiShader::BindAttributes()
{
	BindAttribute(VertexAttributeLocationRule::position, "position");
}

GLuint GuiShader::GetUniformLocation(const char * name)
{
	return glGetUniformLocation(this->GetProgram(), name);
}

void GuiShader::SetTexture(GLuint id)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, id);
	std::string diffuse = "guiTexture";
	int loc = GetUniformLocation(diffuse.c_str());
	if (loc == -1) Debug::Log("GUI texture Setting Fail.");
	glUniform1i(loc, 0);
}

void GuiShader::SetTransformMatrix(glm::mat4 matrix)
{
	int loc = GetUniformLocation("transformation");
	if (loc == -1) Debug::Log("GUI transformation Matrix Setting Fail.");
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
}

void GuiShader::SetTranslation(glm::vec2 move)
{
	int loc = GetUniformLocation("translate");
	if (loc == -1) Debug::Log("GUI translation Setting Fail.");
	glUniform2fv(loc, 1, glm::value_ptr(move));
}

void GuiShader::SetScale(glm::mat4 matrix)
{
	int loc = GetUniformLocation("scale");
	if (loc == -1) Debug::Log("GUI scale Matrix Setting Fail.");
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
}

void GuiShader::SetRotation(glm::mat4 matrix)
{
	int loc = GetUniformLocation("rotate");
	if (loc == -1) Debug::Log("GUI rotate Matrix Setting Fail.");
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
}

void GuiShader::SetOrthoMatrix(glm::mat4 matrix)
{
	int loc = GetUniformLocation("ortho");
	if (loc == -1) Debug::Log("GUI ortho Matrix Setting Fail.");
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
}

void GuiShader::SetScreenSize(glm::vec2 screenSize)
{
	int loc = GetUniformLocation("screenSize");
	if (loc == -1) Debug::Log("GUI screen size Setting Fail.");
	glUniform2fv(loc, 1, glm::value_ptr(screenSize));
}

void GuiShader::SetTextureSize(glm::vec2 texSize)
{
	int loc = GetUniformLocation("texSize");
	if (loc == -1) Debug::Log("GUI texture size Setting Fail.");
	glUniform2fv(loc, 1, glm::value_ptr(texSize));
}
