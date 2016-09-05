#include "Renderer.h"

Renderer::Renderer(StaticShader &shader) : shader(shader)
{
	float width = (float)DisplayManager::GetWindowWidth();
	float height = (float)DisplayManager::GetWindowHeight();
	projectionMatrix = glm::perspective(FOV, (float)width / (float)height, NEAR_PLANE, FAR_PLANE);
}


Renderer::~Renderer()
{
}

void Renderer::Render(Light light, Camera camera, Entity<TextureModel> entity)
{
	TextureModel textureRenderObject = entity.GetModel();
	BasicRenderModel renderObject = entity.GetModel().GetBasicRenderModel();
	shader.StartProgram();
	shader.SetLight(light);
	shader.SetDiffuse(textureRenderObject.GetTextureID());
	shader.SetSpecular(glm::vec3(0.5f));
	shader.SetShininess();
	glm::mat4 modelMatrix;
	modelMatrix = glm::translate(modelMatrix, entity.GetPosition());
	modelMatrix = glm::scale(modelMatrix, glm::vec3(entity.GetScale()));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(entity.GetRotationX()), glm::vec3(1,0,0));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(entity.GetRotationY()), glm::vec3(0,1,0));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(entity.GetRotationZ()), glm::vec3(0,0,1));
	shader.SetModelMatrix(modelMatrix);
	shader.SetViewMatrix(camera.GetViewMatrix());
	shader.SetProjectionMatrix(projectionMatrix);
	glBindVertexArray(renderObject.GetVaoID());
	//glDrawArrays(GL_TRIANGLES, 0, model.GetVertexCount());
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, renderObject.GetVertexCount(), GL_UNSIGNED_INT, 0);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBindVertexArray(0);

	shader.ClearRelativeData();
	shader.StopProgram();
}

void Renderer::Render(Light light, Camera camera, std::map<TextureModel, std::vector<Entity<TextureModel>>> entities)
{
	std::vector<Entity<TextureModel>> values;
	for (std::map<TextureModel, std::vector<Entity<TextureModel>>>::iterator it = entities.begin(); it != entities.end(); ++it)
	{
		PrepareTextureModel(it->first);
		PrepareLight(light);
		std::vector<Entity<TextureModel>> batches = it->second;
		for each (Entity<TextureModel> entity in batches)
		{
			PrepareInstance(camera, entity);
			glBindVertexArray(entity.GetModel().GetBasicRenderModel().GetVaoID());
			glDrawElements(GL_TRIANGLES, entity.GetModel().GetBasicRenderModel().GetVertexCount(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
		UnbindTextureModel();
	}
}

void Renderer::PrepareTextureModel(TextureModel model)
{
	TextureModel textureRenderObject = model;
	BasicRenderModel renderObject = textureRenderObject.GetBasicRenderModel();
	shader.StartProgram();
	shader.SetDiffuse(textureRenderObject.GetTextureID());
	shader.SetSpecular(glm::vec3(0.5f));
	shader.SetShininess();
}

void Renderer::PrepareLight(Light light)
{
	shader.SetLight(light);
}

void Renderer::UnbindTextureModel()
{
	shader.ClearRelativeData();
	shader.StopProgram();
}

void Renderer::PrepareInstance(Camera camera, Entity<TextureModel> entity)
{
	glm::mat4 modelMatrix;
	modelMatrix = glm::translate(modelMatrix, entity.GetPosition());
	modelMatrix = glm::scale(modelMatrix, glm::vec3(entity.GetScale()));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(entity.GetRotationX()), glm::vec3(1, 0, 0));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(entity.GetRotationY()), glm::vec3(0, 1, 0));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(entity.GetRotationZ()), glm::vec3(0, 0, 1));
	shader.SetModelMatrix(modelMatrix);
	shader.SetViewMatrix(camera.GetViewMatrix());
	shader.SetProjectionMatrix(projectionMatrix);
}
