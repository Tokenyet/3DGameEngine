#include "MeshesModel.h"



MeshesModel::MeshesModel()
{
}

MeshesModel::MeshesModel(std::vector<MeshModel> meshes)
{
	this->meshes = meshes;
}

void MeshesModel::SetBoneMap(std::map<std::string, Bone*> bones)
{
	this->boneMap = bones;
}

void MeshesModel::SetAnimation(std::string name, Animation * animation)
{
	if (this->animations.find(name) == this->animations.end())
		this->animations.insert_or_assign(name, animation);
	this->animations[name]->SetBoneMap(this->boneMap);
}

void MeshesModel::SetCurrentAnimation(std::string name)
{
	this->currentAnimationName = name;
}

std::vector<glm::mat4> MeshesModel::MoveAnimation(float time)
{
	std::vector<glm::mat4> boneTransforms;
	if (this->animations.find(this->currentAnimationName) != this->animations.end())
		this->animations[this->currentAnimationName]->MoveAnimation(time, boneTransforms);
	return boneTransforms;
}
