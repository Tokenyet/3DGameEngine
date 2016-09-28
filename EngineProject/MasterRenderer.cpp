#include "MasterRenderer.h"



MasterRenderer::MasterRenderer()
{
	float width = (float)DisplayManager::GetWindowWidth();
	float height = (float)DisplayManager::GetWindowHeight();
	projectionMatrix = glm::perspective(FOV, (float)width / (float)height, NEAR_PLANE, FAR_PLANE);
	shader.Init();
	meshshader.Init();
	cubeShader.Init();
	terrainShader.Init();
	renderer = new Renderer(shader, projectionMatrix);
	meshesRenderer = new MeshesRenderer(meshshader, projectionMatrix);
	lightRenderer = new LightSourceRenderer(cubeShader, projectionMatrix);
	terrainRenderer = new TerrainRenderer(terrainShader, projectionMatrix);
}


MasterRenderer::~MasterRenderer()
{
	delete renderer;
	delete meshesRenderer;
	delete lightRenderer;
	delete terrainRenderer;
}

void MasterRenderer::Prepare()
{
	EnableCulling();
	glEnable(GL_DEPTH_TEST);
	glClearColor(SKY_COLOR.x, SKY_COLOR.y, SKY_COLOR.z, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void MasterRenderer::Render(Light light, Camera camera)
{
	Prepare();
	shader.StartProgram();
	PrepareStaticShader(shader, camera, light);
	renderer->Render(texturedEntities);
	texturedEntities.clear();
	shader.StopProgram();


	lightRenderer->Render(camera, light);

	meshshader.StartProgram();
	PrepareStaticShader(meshshader, camera, light);
	for each (Entity<MeshesModel> meshes in meshesEntities)
		meshesRenderer->Render(meshes);
	meshesEntities.clear();
	meshshader.StopProgram();

	terrainShader.StartProgram();
	PrepareStaticShader(terrainShader, camera, light);
	terrainRenderer->Render(terrains);
	terrains.clear();
	terrainShader.StopProgram();
}

void MasterRenderer::ProcessEntity(Entity<TextureModel> entity)
{
	TextureModel* textureModel = entity.GetModel();
	TextureModel existModel;
	bool checker = false;
	for (std::map<TextureModel, std::vector<Entity<TextureModel>>>::iterator it = texturedEntities.begin(); it != texturedEntities.end(); ++it)
	{
		existModel = it->first;
		if (existModel.GetTexture() == textureModel->GetTexture())
		{
			it->second.push_back(entity);
			return;
		}
	}

	std::vector<Entity<TextureModel>> newBatch;
	newBatch.push_back(entity);
	texturedEntities.insert(std::pair<TextureModel, std::vector<Entity<TextureModel>>>(*textureModel, newBatch));
}

void MasterRenderer::ProcessEntity(Entity<MeshesModel> entity)
{
	meshesEntities.push_back(entity);
}

void MasterRenderer::ProcessEntity(Entity<BasicRenderModel> entity)
{
	basicEntities.push_back(entity);
}

void MasterRenderer::ProcessTerrian(Terrain* terrain)
{
	terrains.push_back(terrain);
}

void MasterRenderer::EnableCulling()
{
	glEnable(GL_CULL_FACE);
}

void MasterRenderer::DisableCulling()
{
	glDisable(GL_CULL_FACE);
}

void MasterRenderer::PrepareStaticShader(StaticShader & shader, Camera camera, Light light)
{
	shader.SetLight(light);
	shader.SetSkyColor(SKY_COLOR);
	shader.SetViewMatrix(camera.GetViewMatrix());
	shader.SetViewPosition(camera.GetCameraPosition());
	shader.SetProjectionMatrix(projectionMatrix);
}
