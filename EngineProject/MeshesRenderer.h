#pragma once
#include "Core.h"
#include "ModelShader.h"
#include "Camera.h"
#include "Entity.h"
#include "MeshesModel.h"
#include "ModelShader.h"

class MeshesRenderer
{
public:
	MeshesRenderer(ModelShader &shader, glm::mat4 projectionMatrix);
	~MeshesRenderer();
	void Render(Entity<MeshesModel> entity);
private:
	ModelShader &shader;
	glm::mat4 projectionMatrix;
	void ProcessMesh(MeshModel model, glm::vec3 position, float scale, glm::vec3 rotation);
};

