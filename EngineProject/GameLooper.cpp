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
	Entity<MeshesModel> mesh(meshesRenderObject, glm::vec3(0, 0, -2), 0, 0, 0, 0.1f);

	std::vector<BasicRenderModel> dragonObject = assimpLoader.GetBasicModel("3dmodel/dragon/dragon.obj");
	TextureModel dragonTextureObject(dragonObject[0], loader.LoadTexture("3dmodel/dragon/white.png"));
	Entity<TextureModel> dragonEntity(dragonTextureObject, glm::vec3(5.0f, 0.0f, -4.0f), 0, 0, 0, 0.5f);

	Light light(glm::vec3(0.2f, 0.2f, -2), loader.LoadRenderModel(CubeShape::Positions, CubeShape::GetPositionLength(),
		CubeShape::Indices, CubeShape::GetIndexLength()));
	Camera camera(glm::vec3(0, 0, 0));
	//MeshesRenderer meshRender(staticShader);
	std::vector<Entity<TextureModel>> cubes;
	cubes.push_back(dragonEntity);
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
	/*cubes.push_back(Entity<TextureModel>(textureRenderObject, glm::vec3(0, 0, -2)
		,0.0f,0.0f,0.0f, 1.0f));*/
	std::vector<Terrain> terrains;
	terrains.push_back(Terrain(0, -1, loader, loader.LoadTexture("images/grass_ground_d.jpg")));
	terrains.push_back(Terrain(-1, -1, loader, loader.LoadTexture("images/grass_ground_d.jpg")));
	while (!DisplayManager::IsCloseRequested())
	{
		//entity.MovePosition(0, 0, -0.01f);
		for each (Entity<TextureModel> entity in cubes)
			masterRenderer.ProcessEntity(entity);
		masterRenderer.ProcessEntity(mesh);
		for each (Terrain terrain in terrains)
			masterRenderer.ProcessTerrian(terrain);
		masterRenderer.Render(light, camera);
		//meshRender.Prepare();
		//meshRender.Render(light, camera, entity);
		//lightRenderer.Prepare();
		//lightRenderer.Render(camera, light);
		// Clear the colorbuffer
		/*glClearColor(0.5f, 0.5f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);*/
		DisplayManager::UpdateDisplay();
		camera.PlayerMove(DisplayManager::GetDeltaTime());
	}
	loader.CleanUp();
	DisplayManager::CloseDisplay();
}
