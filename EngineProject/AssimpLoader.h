#pragma once
#include <sstream>
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include "Core.h"
#include "Loader.h"
#include "StaticShader.h"
#include "MeshModel.h"
#include "MeshesModel.h"

class AssimpLoader
{
public:
	AssimpLoader(Loader &loader);
	MeshesModel GetMeshesModel(std::string path);
	// if model checked by human is one object
	std::vector<BasicRenderModel> GetBasicModel(std::string path);
	~AssimpLoader();
private:
	Loader &loader;
	//MeshesModel model;
	void ProcessNode(aiNode* node, const aiScene* scene, std::vector<MeshModel> &meshes);
	MeshModel ProcessMesh(aiMesh* mesh, const aiScene* scene);
	void ProcessNodeBaiscVersion(aiNode* node, const aiScene* scene, std::vector<BasicRenderModel> &basics);
	BasicRenderModel ProcessMeshBasicVersion(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	std::string directory;
	std::vector<aiString> texturesLoaded;
};

