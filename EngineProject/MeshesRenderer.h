#pragma once
#include "Core.h"
#include "ModelShader.h"
#include "Camera.h"
#include "Entity.h"
#include "MeshesModel.h"

class MeshesRenderer
{
public:
	MeshesRenderer(ModelShader &shader);
	~MeshesRenderer();
	void Prepare();
	void Render(Light light, Camera camera, Entity<MeshesModel> entity);
private:
	ModelShader &shader;
	glm::mat4 projectionMatrix;
	const float FOV = 45.0f;
	const float NEAR_PLANE = 0.1f;
	const float FAR_PLANE = 500.0f;
	void ProcessMesh(MeshModel model, Light light, Camera camera,
		glm::vec3 position, float scale, glm::vec3 rotation);
};

