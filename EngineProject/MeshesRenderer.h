#pragma once
#include "Core.h"
#include "ModelShader.h"
#include "Camera.h"
#include "Entity.h"
#include "MeshesModel.h"

class MeshesRenderer
{
public:
	MeshesRenderer(ModelShader &shader, glm::mat4 projectionMatrix);
	~MeshesRenderer();
	void Render(Light light, Camera camera, Entity<MeshesModel> entity);
private:
	ModelShader &shader;
	glm::mat4 projectionMatrix;
	void ProcessMesh(MeshModel model, Light light, Camera camera,
		glm::vec3 position, float scale, glm::vec3 rotation);
};

