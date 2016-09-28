#include "GuiRenderer.h"
#include "DisplayManager.h"


GuiRenderer::GuiRenderer()
{
	/*float position[] = { -1.0f/2.0f, 1.0f/2.0f,
		-1.0f/2.0f, -1.0f/2.0f,
		1.0f/2.0f, 1.0f/2.0f,
		1.0f/2.0f, -1.0f/2.0f };*/
	//int dataLength = sizeof(position) / sizeof(*position);
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//glBufferData(GL_ARRAY_BUFFER, dataLength * sizeof(float), position, GL_STATIC_DRAW);
	glVertexAttribPointer(VertexAttributeLocationRule::position, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(VertexAttributeLocationRule::position);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	shader.Init();
}


GuiRenderer::~GuiRenderer()
{
}

// Coordination system in GUI is from [negative half of Windows' size to postive]
// Ex: x as -1280/2 ~ 1280/2 , y as -720/2 ~ 720/2
void GuiRenderer::Render(std::vector<GuiTexture> textures)
{
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	for each (GuiTexture texture in textures)
	{
		shader.StartProgram();
		Texture tex = texture.GetTexture();
		shader.SetTexture(tex.GetID());
		glm::vec2 translation = texture.GetPosition();
		glm::mat4 rotation = glm::rotate(glm::mat4(), glm::radians(texture.GetRotation()), glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 scale = glm::scale(glm::mat4(), glm::vec3(texture.GetScale(), 1.0f));
		shader.SetTranslation(translation);
		shader.SetRotation(rotation);
		shader.SetScale(scale);
		shader.SetScreenSize(glm::vec2(DisplayManager::GetWindowWidth(), DisplayManager::GetWindowHeight()));
		shader.SetTextureSize(glm::vec2(tex.GetWidth(), tex.GetHeight()));
		glBindVertexArray(vao);
		float* positions = CalculateInitPosition(tex.GetWidth(), tex.GetHeight());
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), positions, GL_STATIC_DRAW);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(0);
		delete[] positions;
		shader.StopProgram();
	}
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
}

float* GuiRenderer::CalculateInitPosition(int width, int height)
{
	float *position = new float[8] { -1.0f / 2.0f, 1.0f / 2.0f,
		-1.0f / 2.0f, -1.0f / 2.0f,
		1.0f / 2.0f, 1.0f / 2.0f,
		1.0f / 2.0f, -1.0f / 2.0f };
	int length = 8;
	for (int i = 0; i < length; i++)
	{
		if (i % 2 == 0)
			position[i] *= (float)width;
		else
			position[i] *= (float)height;
	}
	return position;
}
