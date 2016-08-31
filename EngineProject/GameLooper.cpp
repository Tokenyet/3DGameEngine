#include "GameLooper.h"
#include "Renderer.h"
#include "Loader.h"
#include "StaticShader.h"
#include "TextureModel.h"

void GameLooper::Loop()
{
	float squad[] = {
		-0.5f,  0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
	};
	int indices[] = {
		0,1,2,
		1,2,3
	};
	float texCoords[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
	};

	DisplayManager::CreateDisplay();
	Renderer render;
	StaticShader staticShader;
	Loader loader;
	/*BasicRenderModel basicRenderObject = 
		loader.LoadRenderModel(squad, sizeof(squad) / sizeof(*squad), indices, sizeof(indices) / sizeof(*indices));*/
	BasicRenderModel basicRenderObject =
		loader.LoadRenderModel(squad, sizeof(squad) / sizeof(*squad),
			indices, sizeof(indices) / sizeof(*indices),
			texCoords, sizeof(texCoords) / sizeof(*texCoords));
	TextureModel textureRenderObject(basicRenderObject, loader.LoadTexture("images/savanna_green_d.jpg"));
	while (!DisplayManager::IsCloseRequested())
	{
		staticShader.StartProgram();
		render.Prepare();
		render.Render(textureRenderObject.GetBasicRenderModel());
		staticShader.SetDiffuseTexture(textureRenderObject.GetTextureID());
		staticShader.ClearRelativeData();
		staticShader.StopProgram();
		// Clear the colorbuffer
		/*glClearColor(0.5f, 0.5f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);*/
		DisplayManager::UpdateDisplay();
	}
	DisplayManager::CloseDisplay();
}
