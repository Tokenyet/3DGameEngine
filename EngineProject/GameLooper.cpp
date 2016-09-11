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
#include "PlayerCamera.h"

#include <vector>
#include <time.h>

void GameLooper::Loop()
{
	DisplayManager::CreateDisplay();
	MasterRenderer masterRenderer;
	Loader loader;
	BasicRenderModel basicRenderObject = 
		loader.LoadRenderModel(CubeShape::Positions, CubeShape::GetPositionLength(),
			CubeShape::Indices, CubeShape::GetIndexLength(),
			CubeShape::TexCoords, CubeShape::GetTexCoordLength(),
			CubeShape::Normals, CubeShape::GetNormalLength());
	//BasicRenderModel basicRenderObject = OBJLoader::LoadObjModel("3dmodel/dragon/dragon.obj", loader);
	//TextureModel textureRenderObject(basicRenderObject, loader.LoadTexture("3dmodel/dragon/white.png"));
	TextureModel textureRenderObject(basicRenderObject, loader.LoadTexture("images/shiny.png"));
	//Entity<TextureModel> entity(textureRenderObject, glm::vec3(0, 0, -10), 0, 0, 0, 1);
	AssimpLoader assimpLoader(loader);
	MeshesModel meshesRenderObject = assimpLoader.GetMeshesModel("3dmodel/nanosuit/nanosuit.obj");
	//Entity<MeshesModel> mesh(meshesRenderObject, glm::vec3(0, 0, -2), 0, 0, 0, 0.1f);

	/*std::vector<BasicRenderModel> dragonObject = assimpLoader.GetBasicModel("3dmodel/dragon/dragon.obj");
	TextureModel dragonTextureObject(dragonObject[0], loader.LoadTexture("3dmodel/dragon/white.png"));
	Entity<TextureModel> dragonEntity(dragonTextureObject, glm::vec3(5.0f, 0.0f, -4.0f), 0, 0, 0, 0.5f);*/

	Light light(glm::vec3(0.2f, 1.0f, -1), loader.LoadRenderModel(CubeShape::Positions, CubeShape::GetPositionLength(),
		CubeShape::Indices, CubeShape::GetIndexLength()));
	//Camera camera(glm::vec3(0, 1.0f, 0));
	//MeshesRenderer meshRender(staticShader);
	std::vector<Entity<TextureModel>> cubes;
	//cubes.push_back(dragonEntity);
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

	std::vector<BasicRenderModel> treeObject = assimpLoader.GetBasicModel("3dmodel/tree/tree.obj");
	TextureModel treeTextureObject(treeObject[0], loader.LoadTexture("3dmodel/tree/tree.png"));
	for (int i = 0; i < 300; i++)
	{
		float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 800.0f - 400.0f;
		float y = 0;
		float z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * -800.0f;
		cubes.push_back(Entity<TextureModel>(treeTextureObject, glm::vec3(x, y, z),
			0.0f, 0.0f,
			0.0f, 2.0f));
	}

	std::vector<BasicRenderModel> grass = assimpLoader.GetBasicModel("3dmodel/grass/grassModel.obj");
	Texture grassTexture = loader.LoadTexture("3dmodel/grass/grassTexture.png");
	grassTexture.SetTransparent(true);
	grassTexture.SetFakeLighting(true);
	TextureModel grassTex(grass[0], grassTexture);
	std::vector<BasicRenderModel> fern = assimpLoader.GetBasicModel("3dmodel/grass/fern.obj");
	Texture fernTexture = loader.LoadTexture("3dmodel/grass/fern.png");
	fernTexture.SetTransparent(true);
	fernTexture.SetFakeLighting(true);
	TextureModel fernTex(fern[0], fernTexture);
	for (int i = 0; i < 100; i++)
	{
		float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 800.0f - 400.0f;
		float y = 0;
		float z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * -400.0f -10.0f;
		Entity<TextureModel> grassEntity(grassTex, glm::vec3(x, y, z), 0, 0, 0, 1.0f);
		x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 800.0f - 400.0f;
		z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * -400.0f;
		Entity<TextureModel> fernEntity(fernTex, glm::vec3(x, y, z), 0, 0, 0, 1.0f);
		cubes.push_back(grassEntity);
		cubes.push_back(fernEntity);
	}

	/*cubes.push_back(Entity<TextureModel>(textureRenderObject, glm::vec3(0, 0, -2)
		,0.0f,0.0f,0.0f, 1.0f));*/
	/**Terrain Start**/
	std::vector<Terrain> terrains;
	Texture background = loader.LoadTexture("images/grass_green_d.jpg");
	Texture rTexture = loader.LoadTexture("images/grass_autumn_orn_d.jpg");
	Texture gTexture = loader.LoadTexture("images/adesert_stone_d.jpg");
	Texture bTexture = loader.LoadTexture("images/island_sand_d.jpg");
	Texture blendMap = loader.LoadTexture("images/blendMap.png");
	TerrainTexturePack pack(background, rTexture, gTexture, bTexture);

	terrains.push_back(Terrain(0, -1, loader, blendMap, pack));
	terrains.push_back(Terrain(-1, -1, loader, blendMap, pack));
	/**Terrain End**/

	/**Player Start**/
	Player<MeshesModel> player(meshesRenderObject, glm::vec3(100, 0, -200), 0, 180.0f, 0, 0.1f);
	PlayerCamera<MeshesModel> playerCamera(player);
	/**Player End**/
	while (!DisplayManager::IsCloseRequested())
	{
		//entity.MovePosition(0, 0, -0.01f);
		float currentTime = (float)glfwGetTime();
		light.MovePosition(glm::sin(currentTime/2.0f)/10.0f, 0.0f, -1 * glm::sin(currentTime/2.0f)/10.0f);
		//light.MovePosition(0.01f, 0.0f, 0.01f);
		for each (Entity<TextureModel> entity in cubes)
			masterRenderer.ProcessEntity(entity);
		masterRenderer.ProcessEntity(player);
		//masterRenderer.ProcessEntity(mesh);
		for each (Terrain terrain in terrains)
			masterRenderer.ProcessTerrian(terrain);
		masterRenderer.Render(light, playerCamera);
		//meshRender.Prepare();
		//meshRender.Render(light, camera, entity);
		//lightRenderer.Prepare();
		//lightRenderer.Render(camera, light);
		// Clear the colorbuffer
		/*glClearColor(0.5f, 0.5f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);*/
		DisplayManager::UpdateDisplay();
		player.PlayerMove(DisplayManager::GetDeltaTime());
		playerCamera.Move(DisplayManager::GetDeltaTime());
		//camera.PlayerMove(DisplayManager::GetDeltaTime());
	}
	loader.CleanUp();
	DisplayManager::CloseDisplay();
}