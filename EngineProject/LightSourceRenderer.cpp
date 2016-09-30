#include "LightSourceRenderer.h"


LightSourceRenderer::LightSourceRenderer(CubeShader &shader, glm::mat4 projectionMatrix) : shader(shader)
{
	this->projectionMatrix = projectionMatrix;
}


LightSourceRenderer::~LightSourceRenderer()
{
}

void LightSourceRenderer::Render(Camera camera, Light light)
{
	BasicRenderModel renderObject = light.GetModel();
	shader.StartProgram();
	glm::mat4 modelMatrix;
	modelMatrix = glm::translate(modelMatrix, light.GetPosition());
	modelMatrix = glm::scale(modelMatrix, glm::vec3(10.0f));
	shader.SetModelMatrix(modelMatrix);
	shader.SetViewMatrix(camera.GetViewMatrix());
	shader.SetProjectionMatrix(projectionMatrix);
	shader.SetLight(light);
	glBindVertexArray(renderObject.GetVaoID());
	//glDrawArrays(GL_TRIANGLES, 0, model.GetVertexCount());
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, renderObject.GetVertexCount(), GL_UNSIGNED_INT, 0);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBindVertexArray(0);
	shader.StopProgram();
}

