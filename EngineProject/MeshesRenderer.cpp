#include "MeshesRenderer.h"

MeshesRenderer::MeshesRenderer(ModelShader &shader, glm::mat4 projectionMatrix) : shader(shader)
{
	this->projectionMatrix = projectionMatrix;
}


MeshesRenderer::~MeshesRenderer()
{
}

void MeshesRenderer::Render(Entity<MeshesModel> entity)
{
	MeshesModel meshesRenderObject = entity.GetModel();
	std::vector<MeshModel> meshes = meshesRenderObject.GetMeshes();
	shader.StartProgram();
	for each (MeshModel model in meshes)
	{
		ProcessMesh(model, entity.GetPosition(), entity.GetScale(),
			glm::vec3(entity.GetRotationX(),entity.GetRotationY(), entity.GetRotationZ()));
	}
	shader.StopProgram();
}

void MeshesRenderer::ProcessMesh(MeshModel model, glm::vec3 position, float scale, glm::vec3 rotation)
{
	BasicRenderModel renderObject = model.GetBasicRenderModel();
	//shader.SetDiffuseTexture(model.GetTextureID());
	glm::mat4 modelMatrix;
	modelMatrix = glm::translate(modelMatrix, position);
	modelMatrix = glm::scale(modelMatrix, glm::vec3(scale));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(1, 0, 0));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0, 1, 0));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0, 0, 1));
	shader.SetModelMatrix(modelMatrix);
	std::map<TextureType, std::vector<Texture>> textures = model.GetTexutres();
	if((int)textures[TextureType::diffuse].size() > 0)
		shader.SetDiffuse(textures[TextureType::diffuse][0].GetID());
	if ((int)textures[TextureType::specular].size() > 0)
		shader.SetSpecular(textures[TextureType::specular][0].GetID());
	shader.SetShininess(32.0f);
	std::vector<glm::mat4> transforms;
	model.MoveAnimation((float)glfwGetTime(), transforms);
	/*for (int i = 0; i < (int)transforms.size(); i++)
		shader.SetBoneTransform(i, transforms[i]);*/
	for (int i = 0; i < (int)transforms.size(); i++)
		shader.SetBoneTransform(i, transforms[i]);

	static int test = 0;
	glUniform1i(glGetUniformLocation(shader.GetProgram(), "test"), test);
	if (Keyboard::GetKey(GLFW_KEY_K))
	{
		test++;
		Debug::Log(std::to_string(test));
	}
	glBindVertexArray(renderObject.GetVaoID());
	//glDrawArrays(GL_TRIANGLES, 0, model.GetVertexCount());
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, renderObject.GetVertexCount(), GL_UNSIGNED_INT, 0);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBindVertexArray(0);
	shader.ClearRelativeData();
}
