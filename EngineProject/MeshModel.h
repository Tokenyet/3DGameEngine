#pragma once
#include "BasicRenderModel.h"
#include "Texture.h"
#include <map>

enum TextureType {
	diffuse,
	specular,
	normaltexture,
};

struct BoneKey
{
	double time;
	glm::vec3 vector;
	glm::quat rotation;
};

struct Bone {
	int index;
	glm::mat4 inverseBindPoseMatrix;
	std::vector<BoneKey> rotationKeys;
	std::vector<BoneKey> scalingKeys;
	std::vector<BoneKey> transformKeys;
	glm::mat4 nodeTransform; // getParent * transform * local
	glm::mat4 transform; // node to parent space
	glm::mat4 localTransform; // T R S
	glm::mat4 finalTransform; // globalInverse * nodeTransform * inverse 
	Bone* parent;
	std::vector<Bone*> children;
	glm::mat4 getParentTransform();
};

class MeshModel
{
public:
	MeshModel();
	MeshModel(BasicRenderModel model, std::map<TextureType, std::vector<Texture>> textures);
	void SetAnimationInfos(std::string name, glm::mat4 globalInverse, std::map<std::string, Bone*> boneMap, float tickPerSec, float duraction);
	void MoveAnimation(float time, std::vector<glm::mat4>& boneTransforms);
	BasicRenderModel GetBasicRenderModel();
	std::map<TextureType, std::vector<Texture>> GetTexutres();
private:
	BasicRenderModel model;
	std::map<TextureType, std::vector<Texture>> textures;
	glm::mat4 globalInverse;
	std::map<std::string, Bone*> boneMap;
	std::vector<Bone*> indexBones;
	float tickPerSecond;
	float duration;
	void UpdateAnimations(float time, std::vector<Bone*>& bones);
	Bone* FindRootBone(const std::vector<Bone*>& bones);
	void UpdateBone(Bone* bone = NULL);
	glm::mat4 GetInterpolateRotation(float time, std::vector<BoneKey>& keys);
	glm::mat4 GetInterpolateTransform(float time, std::vector<BoneKey>& keys);
	glm::mat4 GetInterpolateScaling(float time, std::vector<BoneKey>& keys);
	int FindBestTimeIndex(float time, std::vector<BoneKey>& keys);
};

