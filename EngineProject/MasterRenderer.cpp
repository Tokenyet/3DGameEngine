#include "MasterRenderer.h"



MasterRenderer::MasterRenderer()
{
	renderer = new Renderer(shader);
	meshesRenderer = new MeshesRenderer(meshshader);
	lightRenderer = new LightSourceRenderer(cubeShader);
}


MasterRenderer::~MasterRenderer()
{
	delete renderer;
	delete meshesRenderer;
	delete lightRenderer;
}

void MasterRenderer::Prepare()
{
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.5f, 0.5f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void MasterRenderer::Render(Light light, Camera camera)
{
	Prepare();
	renderer->Render(light, camera, texturedEntities);
	for each (Entity<MeshesModel> meshes in meshesEntities)
		meshesRenderer->Render(light, camera, meshes);
	texturedEntities.clear();
	lightRenderer->Render(camera, light);
	meshesEntities.clear();
}

void MasterRenderer::ProcessEntity(Entity<TextureModel> entity)
{
	TextureModel textureModel = entity.GetModel();
	TextureModel existModel;
	bool checker = false;
	for (std::map<TextureModel, std::vector<Entity<TextureModel>>>::iterator it = texturedEntities.begin(); it != texturedEntities.end(); ++it)
	{
		existModel = it->first;
		if (existModel.GetTextureID() == textureModel.GetTextureID())
		{
			it->second.push_back(entity);
			return;
		}
	}

	std::vector<Entity<TextureModel>> newBatch;
	newBatch.push_back(entity);
	texturedEntities.insert(std::pair<TextureModel, std::vector<Entity<TextureModel>>>(textureModel, newBatch));
}

void MasterRenderer::ProcessEntity(Entity<MeshesModel> entity)
{
	meshesEntities.push_back(entity);
}

void MasterRenderer::ProcessEntity(Entity<BasicRenderModel> entity)
{
	basicEntities.push_back(entity);
}
