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
	MeshesModel GetMeshesModel(std::string path, bool rightHandSide = false);
	Animation* LoadAnimation(std::string path, bool rightHandSide = false);
	// if model checked by human is one object
	std::vector<BasicRenderModel> GetBasicModel(std::string path);
	~AssimpLoader();
private:
	Loader &loader;
	//MeshesModel model;
	void ProcessNode(aiNode* node, const aiScene* scene, std::vector<MeshModel> &meshes, std::map<std::string, Bone*> &boneMap);
	MeshModel ProcessMesh(aiMesh* mesh, const aiScene* scene, std::map<std::string, Bone*> &boneMap);
	void ProcessNodeBaiscVersion(aiNode* node, const aiScene* scene, std::vector<BasicRenderModel> &basics);
	BasicRenderModel ProcessMeshBasicVersion(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	std::string directory;
	std::vector<aiString> texturesLoaded;

	// right hand side
	bool rightHandSide = false;
	glm::mat3 TRANSFORM_TO_LEFT_HAND_SIDE = glm::mat3(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	// bone
	void LoadBoneAnimation(const aiScene* scene, std::map<std::string, Bone*>& boneMap);
	void LoadBoneBasicTransform(const aiAnimation* animation, const aiNode* parentNode, const aiNode* childNode, std::map<std::string, Bone*>& boneMap);
	const aiNodeAnim* FindNodeAnim(const aiAnimation* animation, std::string nodeName);
};

