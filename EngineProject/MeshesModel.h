#pragma once
#include "MeshModel.h"
#include "Animation.h"

class MeshesModel
{
public:
	MeshesModel();
	MeshesModel(std::vector<MeshModel> meshes);
	void SetBoneMap(std::map<std::string, Bone*> bones);
	void SetAnimation(std::string name, Animation* animation);
	void SetCurrentAnimation(std::string name);
	std::vector<glm::mat4> MoveAnimation(float time);
	std::map<std::string, Animation*> GetAnimations() {	return this->animations; }
	std::vector<MeshModel> GetMeshes() { return this->meshes; }
private:
	std::vector<MeshModel> meshes;
	std::map<std::string, Bone*> boneMap;
	std::map<std::string, Animation*> animations;
	std::string currentAnimationName;
	//glm::mat4 globalInverse;
};

