#include "GameLooper.h"
#include "Renderer.h"
#include "Loader.h"
#include "StaticShader.h"
#include "TextureModel.h"
#include "Entity.h"
#include "Camera.h"
#include "OBJLoader.h"
#include "AssimpLoader.h"
#include "MeshesRenderer.h"
#include "CubeShape.h"
#include "CubeShader.h"
#include "LightSourceRenderer.h"
#include "MasterRenderer.h"
#include "TerrainTexturePack.h"
#include "Player.h"
#include "CustomPlayer.h"
#include "PlayerCamera.h"
#include "GuiRenderer.h"
#include "PointLight.h"

#include <vector>
#include <time.h>

void GameLooper::Loop()
{
	// Create Display for windows
	DisplayManager::CreateDisplay();
	// Create MasterRenderer for render anything.
	MasterRenderer masterRenderer;
	// Create Loader for load texture, image, basic render model....etc.
	Loader loader;

	/* Cube Basic Render Object */
	BasicRenderModel basicRenderObject = 
		loader.LoadRenderModel(CubeShape::Positions, CubeShape::GetPositionLength(),
			CubeShape::Indices, CubeShape::GetIndexLength(),
			CubeShape::TexCoords, CubeShape::GetTexCoordLength(),
			CubeShape::Normals, CubeShape::GetNormalLength());
	/* Gvie a view on Cube Model */
	TextureModel textureRenderObject(basicRenderObject, loader.LoadTexture("images/shiny.png"));
	/* Cube Collection */
	std::vector<Entity<TextureModel>> cubes;
	/* Make 200 cubes for rendereing, and take a Entity for basic position */
	srand((unsigned)time(NULL));
	for (int i = 0; i < 200; i++)
	{
		float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 100.0f - 50.0f;
		float y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 100.0f - 50.0f;
		float z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * -300.0f;
		cubes.push_back(Entity<TextureModel>(textureRenderObject, glm::vec3(x, y, z),
			static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 180.0f,
			static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 180.0f,
			0.0f, 1.0f));
	}


	// Use assimp loader to quick loading, and Loader for resource management.
	AssimpLoader assimpLoader(loader);

	// MeshesModel represent a mesh collection for a model.
	//MeshesModel meshesRenderObject = assimpLoader.GetMeshesModel("3dmodel/nanosuit/nanosuit.obj");
	MeshesModel meshesRenderObject = assimpLoader.GetMeshesModel("3dmodel/mycharacter/mycharacter.dae");
	Animation *animation = assimpLoader.LoadAnimation("3dmodel/mycharacter/mycharacter.fbx", true);
	Animation *idleAnimation = assimpLoader.LoadAnimation("3dmodel/mycharacter/mycharacter-idle.dae", true);
	meshesRenderObject.SetAnimation("Walk", animation);
	meshesRenderObject.SetAnimation("Idle", idleAnimation);
	/** Player Start **/
	// Suit a player model for MeshesModel, just like normal Entity using.
	//Player<MeshesModel> player(meshesRenderObject, glm::vec3(100, 0, -200), 0, 180.0f, 0, 0.1f);
	CustomPlayer player(meshesRenderObject, glm::vec3(100, 0, -200), 0, 180.0f, 0, 0.1f);
	// Make a third player camera
	PlayerCamera<MeshesModel> playerCamera(player);
	/** Player End **/

	// Light for global lighting.
	/*Light light(glm::vec3(0.2f, 1.0f, -1), loader.LoadRenderModel(CubeShape::Positions, CubeShape::GetPositionLength(),
		CubeShape::Indices, CubeShape::GetIndexLength()));*/
	DirLight dirLight(glm::vec3(100.0f, 100.0f, 100.0f), loader.LoadRenderModel(CubeShape::Positions, CubeShape::GetPositionLength(),
		CubeShape::Indices, CubeShape::GetIndexLength()), glm::vec3(-1.0f, 0.0f, 0.0f));
	dirLight.SetColorParameter(glm::vec3(0.4f, 0.4f, 0.4f));
	PointLight pointLight(glm::vec3(100.0f, 0.0f, -200.0f), loader.LoadRenderModel(CubeShape::Positions, CubeShape::GetPositionLength(),
		CubeShape::Indices, CubeShape::GetIndexLength()));
	std::vector<Light*> lights;
	lights.push_back(&dirLight);
	lights.push_back(&pointLight);

	/** Terrain Start **/
	std::vector<Terrain*> terrains;
	Texture background = loader.LoadTexture("images/grass_green_d.jpg");
	Texture rTexture = loader.LoadTexture("images/grass_autumn_orn_d.jpg");
	Texture gTexture = loader.LoadTexture("images/adesert_stone_d.jpg");
	Texture bTexture = loader.LoadTexture("images/island_sand_d.jpg");
	Texture blendMap = loader.LoadTexture("images/blendMap.png");
	TerrainTexturePack pack(background, rTexture, gTexture, bTexture);

	terrains.push_back(new Terrain(0, -1, loader, blendMap, pack, "images/heightmap.png"));
	terrains.push_back(new Terrain(-1, -1, loader, blendMap, pack));
	/** Terrain End **/

	/* 200 Tree Objects */
	std::vector<BasicRenderModel> treeObject = assimpLoader.GetBasicModel("3dmodel/tree/tree.obj");
	TextureModel treeTextureObject(treeObject[0], loader.LoadTexture("3dmodel/tree/tree.png"));
	for (int i = 0; i < 300; i++)
	{
		float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 800.0f - 400.0f;
		float z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * -800.0f;
		float y = terrains[0]->GetHeightByPosition(x, z);
		cubes.push_back(Entity<TextureModel>(treeTextureObject, glm::vec3(x, y, z),
			0.0f, 0.0f,
			0.0f, 2.0f));
	}

	/* 200 Grass Objects */
	std::vector<BasicRenderModel> grass = assimpLoader.GetBasicModel("3dmodel/grass/grassModel.obj");
	Texture grassTexture = loader.LoadTexture("3dmodel/grass/grassTexture.png");
	grassTexture.SetTransparent(true);
	grassTexture.SetFakeLighting(true);
	TextureModel grassTex(grass[0], grassTexture);
	std::vector<BasicRenderModel> fern = assimpLoader.GetBasicModel("3dmodel/grass/fern.obj");
	Texture fernTexture = loader.LoadTexture("3dmodel/grass/fern-atl.png");
	int fernAtlasesRow = 2;
	fernTexture.SetTextureRowAtlaseCount(fernAtlasesRow);
	fernTexture.SetTransparent(true);
	fernTexture.SetFakeLighting(true);
	TextureModel fernTex(fern[0], fernTexture);
	for (int i = 0; i < 100; i++)
	{
		float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 800.0f - 400.0f;
		float z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * -400.0f -10.0f;
		float y = terrains[0]->GetHeightByPosition(x, z);
		Entity<TextureModel> grassEntity(grassTex, glm::vec3(x, y, z), 0, 0, 0, 1.0f);
		x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 800.0f - 400.0f;
		z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * -400.0f;
		y = terrains[0]->GetHeightByPosition(x, z);
		Entity<TextureModel> fernEntity(fernTex, glm::vec3(x, y, z), 0, 0, 0, 1.0f, rand() % (fernAtlasesRow * fernAtlasesRow));
		cubes.push_back(grassEntity);
		cubes.push_back(fernEntity);
	}

	std::vector<GuiTexture> guis;
	guis.push_back(GuiTexture(loader.LoadTexture("images/sword.png"), glm::vec2(-600.0f), 30.0f, glm::vec2(0.25f)));
	guis.push_back(GuiTexture(loader.LoadTexture("images/title.png"), glm::vec2(600.0f), 0.0f, glm::vec2(0.30f)));
	GuiRenderer guiRenderer;

	while (!DisplayManager::IsCloseRequested())
	{
		float currentTime = (float)glfwGetTime();
		for each (Entity<TextureModel> entity in cubes)
			masterRenderer.ProcessEntity(entity);
		masterRenderer.ProcessEntity(player);
		for each (Terrain *terrain in terrains)
			masterRenderer.ProcessTerrian(terrain);
		masterRenderer.Render(lights, playerCamera);
		guiRenderer.Render(guis);
		DisplayManager::UpdateDisplay();
		player.PlayerMove(terrains[0] , (float)Time::GetDeltaTime());
		playerCamera.Move((float)Time::GetDeltaTime());

		pointLight.MovePosition(glm::sin(glm::radians((float)Time::GetNowTime() * 50.0f)), 0.0f, glm::sin(glm::radians((float)Time::GetNowTime() * 50.0f)));
	}
	loader.CleanUp();
	/*for each (Terrain *terrain in terrains)
		delete terrain;*/
	DisplayManager::CloseDisplay();
}