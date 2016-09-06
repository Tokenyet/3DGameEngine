#include "TerrainRenderer.h"



TerrainRenderer::TerrainRenderer(TerrainShader &shader, glm::mat4 projectionMatrix) : shader(shader)
{
	this->projectionMatrix = projectionMatrix;
}


TerrainRenderer::~TerrainRenderer()
{
}

void TerrainRenderer::Render(Light light, Camera camera, std::vector<Terrain> terrains)
{
	for each (Terrain terrain in terrains)
	{
		PrepareTextureModel(terrain.GetTexture());
		PrepareLight(light);
		PrepareInstance(camera, terrain);
		glBindVertexArray(terrain.GetModel().GetVaoID());
		glDrawElements(GL_TRIANGLE_STRIP, terrain.GetModel().GetVertexCount(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		UnbindTextureModel();
	}
}


void TerrainRenderer::PrepareTextureModel(Texture texture)
{
	shader.StartProgram();
	shader.SetDiffuse(texture.ID);
	shader.SetSpecular(glm::vec3(1.0f));
	shader.SetShininess();
}

void TerrainRenderer::PrepareLight(Light light)
{
	shader.SetLight(light);
}

void TerrainRenderer::UnbindTextureModel()
{
	shader.ClearRelativeData();
	shader.StopProgram();
}

void TerrainRenderer::PrepareInstance(Camera camera, Terrain terrain)
{
	glm::mat4 modelMatrix;
	modelMatrix = glm::translate(modelMatrix, terrain.GetPosition());
	modelMatrix = glm::scale(modelMatrix, glm::vec3(1.0f));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(0.0f), glm::vec3(1, 0, 0));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(0.0f), glm::vec3(0, 1, 0));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(0.0f), glm::vec3(0, 0, 1));
	shader.SetModelMatrix(modelMatrix);
	shader.SetViewMatrix(camera.GetViewMatrix());
	shader.SetProjectionMatrix(projectionMatrix);
}
