#pragma once
#include "Core.h"
#include "DisplayManager.h"
#include "BasicRenderModel.h"
#include "StaticShader.h"
#include "Entity.h"
#include "Camera.h"
#include <unordered_map>

class Renderer
{
public:
	Renderer(StaticShader &shader);
	~Renderer();
	void Render(Light light, Camera camera, Entity<TextureModel> entity);
	void Render(Light light, Camera camera, std::map <TextureModel, std::vector<Entity<TextureModel>>> entities);
private:
	StaticShader &shader;
	glm::mat4 projectionMatrix;
	const float FOV = 45.0f;
	const float NEAR_PLANE = 0.1f;
	const float FAR_PLANE = 500.0f;
	void PrepareTextureModel(TextureModel model);
	void PrepareLight(Light light);
	void UnbindTextureModel();
	void PrepareInstance(Camera camera, Entity<TextureModel> entity);
};

