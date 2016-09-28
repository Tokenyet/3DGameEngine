#pragma once
#include "ShaderProgram.h"
class GuiShader :
	public ShaderProgram
{
private:
	static const char * VERTEX_SHADER;
	static const char * FRAGMENT_SHADER;
public:
	GuiShader();
	GuiShader(const char* vertex, const char* fragment);
	void SetTexture(GLuint id);
	void SetTransformMatrix(glm::mat4 matrix);
	void SetTranslation(glm::vec2 move);
	void SetScale(glm::mat4 matrix);
	void SetRotation(glm::mat4 matrix);
	void SetOrthoMatrix(glm::mat4 matrix);
	void SetScreenSize(glm::vec2 screenSize);
	void SetTextureSize(glm::vec2 texSize);
	~GuiShader();
protected:
	virtual void BindAttributes();
	GLuint GetUniformLocation(const char* name);
};

