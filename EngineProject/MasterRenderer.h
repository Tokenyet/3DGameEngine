#pragma once
#include "Core.h"
#include "DisplayManager.h"
#include "BasicRenderModel.h"
#include "StaticShader.h"
#include "LightSourceRenderer.h"
#include "Renderer.h"
#include "MeshesRenderer.h"
#include "LightSourceRenderer.h"
#include "Entity.h"
#include "Camera.h"

#include <map>

class MasterRenderer
{
public:
	MasterRenderer();
	~MasterRenderer();
	void Prepare();
	void Render(Light light, Camera camera);
	void ProcessEntity(Entity<TextureModel> entity);
	void ProcessEntity(Entity<MeshesModel> entity);
	void ProcessEntity(Entity<BasicRenderModel> entity);
private:
	std::map<TextureModel, std::vector<Entity<TextureModel>>> texturedEntities;
	std::vector<Entity<BasicRenderModel>> basicEntities;
	StaticShader shader;
	Renderer *renderer;
	std::vector<Entity<MeshesModel>> meshesEntities;
	MeshesRenderer *meshesRenderer;
	ModelShader meshshader;
	CubeShader cubeShader;
	std::vector<Light> lights;
	LightSourceRenderer *lightRenderer;
	glm::mat4 projectionMatrix;
	const float FOV = 45.0f;
	const float NEAR_PLANE = 0.1f;
	const float FAR_PLANE = 500.0f;
};


