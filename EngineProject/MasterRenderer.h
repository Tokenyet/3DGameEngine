#pragma once
#include "Core.h"
#include "DisplayManager.h"
#include "BasicRenderModel.h"
#include "StaticShader.h"
#include "TerrainShader.h"
#include "CubeShader.h"
#include "Renderer.h"
#include "MeshesRenderer.h"
#include "LightSourceRenderer.h"
#include "TerrainRenderer.h"
#include "Core.h"
#include "Entity.h"
#include "Camera.h"
#include "GuiTexture.h"
#include "GuiRenderer.h"

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
	void ProcessTerrian(Terrain* entity);
	static void EnableCulling();
	static void DisableCulling();
private:
	const glm::vec3 SKY_COLOR = glm::vec3(0.5f, 0.5f, 0.3f);
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
	TerrainShader terrainShader;
	std::vector<Terrain*> terrains;
	TerrainRenderer *terrainRenderer;
	glm::mat4 projectionMatrix;
	const float FOV = 45.0f;
	const float NEAR_PLANE = 0.1f;
	const float FAR_PLANE = 500.0f;
	void PrepareStaticShader(StaticShader &shader, Camera camera, Light light);
};


