#include "Animation.h"



Animation::Animation()
{
}

Animation::Animation(std::string name, glm::mat4 globalInverse, std::map<std::string, Bone*> boneMap, float tickPerSec, float duraction)
{
	SetAnimationInfos(name, globalInverse, boneMap, tickPerSec, duraction);
}


Animation::~Animation()
{
}


void Animation::SetAnimationInfos(std::string name, glm::mat4 globalInverse, std::map<std::string, Bone*> boneMap, float tickPerSec, float durations)
{
	this->globalInverse = globalInverse;
	this->boneMap = boneMap;
	//this->indexBones.resize(this->boneMap.size());
	/*for (std::map<std::string, Bone*>::iterator it = this->boneMap.begin(); it != this->boneMap.end(); it++)
		indexBones[it->second->index] = it->second;*/
	this->tickPerSecond = tickPerSec;
	this->duration = durations;
}

void Animation::SetBoneMap(std::map<std::string, Bone*>& boneMap)
{
	int index = 0;
	std::vector<Bone*> outOfBoneMap;
	for (std::map<std::string, Bone*>::iterator it = this->boneMap.begin(); it != this->boneMap.end(); it++)
	{
		Bone *currentBone = this->boneMap[it->first];
		if (boneMap.find(it->first) != boneMap.end())
		{
			currentBone->inverseBindPoseMatrix = boneMap[it->first]->inverseBindPoseMatrix;
			currentBone->index = boneMap[it->first]->index;
		}
		else
		{
			outOfBoneMap.push_back(currentBone);
		}
		index++;
	}
	index--;

	for(int i = (int)outOfBoneMap.size() - 1; i >= 0;i--)
	{
		outOfBoneMap[i]->index = index;
		index--;
	}

	this->indexBones.resize(this->boneMap.size());
	for (std::map<std::string, Bone*>::iterator it = this->boneMap.begin(); it != this->boneMap.end(); it++)
	{
		indexBones[it->second->index] = it->second;
	}
}

void Animation::MoveAnimation(float time, std::vector<glm::mat4>& boneTransforms)
{
	float ticksPerSecond = tickPerSecond != 0 ?
		tickPerSecond : 25.0f;
	float TimeInTicks = time * ticksPerSecond;
	float AnimationTime = fmod(TimeInTicks, duration);
	UpdateAnimations(AnimationTime, indexBones);
	Bone *rootBone = FindRootBone(indexBones);
	UpdateBone(rootBone);
	boneTransforms.resize(indexBones.size());

	for (int i = 0; i < (int)indexBones.size(); i++)
	{
		/*if (i == 2)
		Debug::Log(indexBones[i]->finalTransform);*/
		boneTransforms[i] = indexBones[i]->finalTransform;
	}
}


void Animation::UpdateAnimations(float time, std::vector<Bone*>& bones)
{
	for each (Bone* bone in bones)
	{
		glm::mat4 rotate = GetInterpolateRotation(time, bone->rotationKeys);
		glm::mat4 transform = GetInterpolateTransform(time, bone->transformKeys);
		glm::mat4 scaling = GetInterpolateScaling(time, bone->scalingKeys);
		/*glm::mat4 localTransform = transform * scaling * glm::mat4(1.0f);
		bone->localTransform = localTransform;
		std::string boneName;
		for (std::map<std::string, Bone*>::iterator it = boneMap.begin(); it != boneMap.end(); it++)
		{
		if (it->second->index == bone->index)
		{
		boneName = it->first;
		Debug::Log(it->first);
		}
		}
		Debug::Log(bone->localTransform);*/
		//bone->localTransform = transform * scaling * rotate;
		bone->localTransform = transform * scaling * rotate;
		//bone->localTransform = transform * scaling * glm::mat4(1.0f);
		//bone->localTransform = glm::mat4(1.0f) * scaling * rotate;
		//bone->localTransform = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f));
		//bone->localTransform = glm::mat4(1.0f);
	}
}

Bone * Animation::FindRootBone(const std::vector<Bone*>& bones)
{
	Bone* bone = bones[0];
	for (int i = 0; i < (int)bones.size(); i++)
	{
		if (bone->parent == nullptr)
			return bone;
		bone = bone->parent;
	}
	return nullptr;
}

void Animation::UpdateBone(Bone * bone)
{
	std::string boneName = "";
	std::string parentName = "";
	for (std::map<std::string, Bone*>::iterator it = boneMap.begin(); it != boneMap.end(); it++)
	{
		if (it->second->index == bone->index)
			boneName = it->first;
		if (bone->parent != nullptr && it->second->index == bone->parent->index)
			parentName = it->first;
	}
	if (parentName != "")
		Debug::Log("parent:" + parentName);
	Debug::Log("bone:" + boneName);
	glm::mat4 parentTransform = bone->getParentTransform();

	if (boneName == "Scene" || boneName == "Armature")
	{
		bone->nodeTransform = parentTransform // This retrieve the transformation one level above in the tree
			* bone->transform //bone->transform is the assimp matrix assimp_node->mTransformation
			* bone->localTransform;  //this is your T * R matrix
	}
	else
	{
		bone->nodeTransform = parentTransform // This retrieve the transformation one level above in the tree
			* bone->localTransform;  //this is your T * R matrix
	}

	bone->finalTransform = globalInverse // which is scene->mRootNode->mTransformation from assimp
		* bone->nodeTransform  //defined above
		* bone->inverseBindPoseMatrix;  //which is ai_mesh->mBones[i]->mOffsetMatrix

										//Debug::Log(bone->finalTransform);
	for (int i = 0; i < (int)bone->children.size(); i++) {
		UpdateBone(bone->children[i]);
	}
}

glm::mat4 Animation::GetInterpolateRotation(float time, std::vector<BoneKey>& keys)
{
	// we need at least two values to interpolate...
	if ((int)keys.size() == 0) {
		return glm::mat4(1.0f);
	}
	if ((int)keys.size() == 1) {
		return glm::mat4_cast(keys[0].rotation);
	}

	int rotationIndex = FindBestTimeIndex(time, keys);
	int nextRotationIndex = (rotationIndex + 1);
	assert(nextRotationIndex < (int)keys.size());
	float DeltaTime = (float)(keys[nextRotationIndex].time - keys[rotationIndex].time);
	float Factor = (time - (float)keys[rotationIndex].time) / DeltaTime;
	if (Factor < 0.0f)
		Factor = 0.0f;
	if (Factor > 1.0f)
		Factor = 1.0f;
	assert(Factor > 0.0f && Factor < 1.0f);
	const glm::quat& startRotationQ = keys[rotationIndex].rotation;
	const glm::quat& endRotationQ = keys[nextRotationIndex].rotation;
	glm::quat interpolateQ = glm::lerp(startRotationQ, endRotationQ, Factor);
	interpolateQ = glm::normalize(interpolateQ);
	return glm::mat4_cast(interpolateQ);
}

glm::mat4 Animation::GetInterpolateTransform(float time, std::vector<BoneKey>& keys)
{
	// we need at least two values to interpolate...
	if ((int)keys.size() == 0) {
		return glm::mat4(1.0f);
	}
	if ((int)keys.size() == 1) {
		return glm::translate(glm::mat4(1.0f), keys[0].vector);
	}

	int translateIndex = FindBestTimeIndex(time, keys);
	int nextTranslateIndex = (translateIndex + 1);
	assert(nextTranslateIndex < (int)keys.size());
	float DeltaTime = (float)(keys[nextTranslateIndex].time - keys[translateIndex].time);
	float Factor = (time - (float)keys[translateIndex].time) / DeltaTime;
	if (Factor < 0.0f)
		Factor = 0.0f;
	if (Factor > 1.0f)
		Factor = 1.0f;
	assert(Factor > 0.0f && Factor < 1.0f);
	const glm::vec3& startTranslate = keys[translateIndex].vector;
	const glm::vec3& endTrabslate = keys[nextTranslateIndex].vector;
	glm::vec3 delta = endTrabslate - startTranslate;
	glm::vec3 resultVec = startTranslate + delta * Factor;
	return glm::translate(glm::mat4(1.0f), resultVec);
}

glm::mat4 Animation::GetInterpolateScaling(float time, std::vector<BoneKey>& keys)
{
	// we need at least two values to interpolate...
	if ((int)keys.size() == 0) {
		return glm::mat4(1.0f);
	}
	if ((int)keys.size() == 1) {
		return glm::scale(glm::mat4(1.0f), keys[0].vector);
	}

	int scalingIndex = FindBestTimeIndex(time, keys);
	int nextScalingIndex = (scalingIndex + 1);
	assert(nextScalingIndex < (int)keys.size());
	float DeltaTime = (float)(keys[nextScalingIndex].time - keys[scalingIndex].time);
	float Factor = (time - (float)keys[scalingIndex].time) / DeltaTime;
	if (Factor < 0.0f)
		Factor = 0.0f;
	if (Factor > 1.0f)
		Factor = 1.0f;
	assert(Factor > 0.0f && Factor < 1.0f);
	const glm::vec3& startScaling = keys[scalingIndex].vector;
	const glm::vec3& endScaling = keys[nextScalingIndex].vector;
	glm::vec3 delta = endScaling - startScaling;
	glm::vec3 resultVec = startScaling + delta * Factor;
	return glm::scale(glm::mat4(1.0f), resultVec);
}

int Animation::FindBestTimeIndex(float time, std::vector<BoneKey>& keys)
{
	for (int i = 0; i < (int)keys.size() - 1; i++) {
		if (time < (float)keys[i + 1].time) {
			return i;
		}
	}
	return (int)keys.size() - 2;
}

glm::mat4 Bone::getParentTransform()
{
	if (this->parent != nullptr)
		return parent->nodeTransform;
	else
		return glm::mat4(1.0f);
}

