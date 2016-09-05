#include "LightSourceRenderer.h"


LightSourceRenderer::LightSourceRenderer(CubeShader &shader) : shader(shader)
{
	float width = (float)DisplayManager::GetWindowWidth();
	float height = (float)DisplayManager::GetWindowHeight();
	projectionMatrix = glm::perspective(FOV, (float)width / (float)height, NEAR_PLANE, FAR_PLANE);
}


LightSourceRenderer::~LightSourceRenderer()
{
}

void LightSourceRenderer::Prepare()
{
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.5f, 0.5f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void LightSourceRenderer::Render(Camera camera, Light light)
{
	BasicRenderModel renderObject = light.GetModel();
	shader.StartProgram();
	glm::mat4 modelMatrix;
	modelMatrix = glm::translate(modelMatrix, light.GetPosition());
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
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

