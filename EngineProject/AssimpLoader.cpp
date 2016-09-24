#include "AssimpLoader.h"

AssimpLoader::AssimpLoader(Loader & loader) : loader(loader)
{
}

MeshesModel AssimpLoader::GetMeshesModel(std::string path)
{
	std::vector<MeshModel> meshes;
	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
		throw "no model error";
	}
	this->directory = path.substr(0, path.find_last_of('/'));

	this->ProcessNode(scene->mRootNode, scene, meshes);
	this->texturesLoaded.clear();
	return MeshesModel(meshes);
}

std::vector<BasicRenderModel> AssimpLoader::GetBasicModel(std::string path)
{
	std::vector<BasicRenderModel> basics;
	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
		throw "no model error";
	}
	this->directory = path.substr(0, path.find_last_of('/'));

	this->ProcessNodeBaiscVersion(scene->mRootNode, scene, basics);
	this->texturesLoaded.clear();
	return basics;
}

AssimpLoader::~AssimpLoader()
{
}

void AssimpLoader::ProcessNode(aiNode * node, const aiScene * scene, std::vector<MeshModel> &meshes)
{
	// Process all the node's meshes (if any)
	for (GLuint i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(this->ProcessMesh(mesh, scene));
	}
	/*glm::mat4 mat4mat = glm::make_mat4<float>(node->mTransformation[0]);
	mat4mat = glm::transpose(mat4mat);
	float *matrix = glm::value_ptr(mat4mat);
	Debug::Log("Matrix:");
	std::string s;
	for (int i = 0; i < 16; i++)
	{
		s += std::to_string(matrix[i]) + ",";
		if ((i + 1) % 4 == 0)
			s += "\r\n";
	}
	s += "\r\n";
	Debug::Log(s);*/

	// Then do the same for each of its children
	for (GLuint i = 0; i < node->mNumChildren; i++)
	{
		this->ProcessNode(node->mChildren[i], scene, meshes);
	}
}

MeshModel AssimpLoader::ProcessMesh(aiMesh * mesh, const aiScene * scene)
{
	//std::vector<Vertex> vertices;
	float *vertices = new float[mesh->mNumVertices * 3];
	int vertexLength = mesh->mNumVertices * 3;
	float *normals = new float[mesh->mNumVertices * 3];
	int normalLength = mesh->mNumVertices * 3;
	float *texCoords = new float[mesh->mNumVertices * 2];
	int texCoordLength = mesh->mNumVertices * 2;
	std::vector<int> indicesList;
	int *indices;
	int indexLength;

	//std::vector<Texture> textures;
	std::map<TextureType, std::vector<Texture>> textures;
	for (GLuint i = 0; i < mesh->mNumVertices; i++)
	{
		// Process vertex positions, normals and texture coordinates
		vertices[i * 3] = mesh->mVertices[i].x;
		vertices[i * 3 + 1] = mesh->mVertices[i].y;
		vertices[i * 3 + 2] = mesh->mVertices[i].z;
		normals[i * 3] = mesh->mNormals[i].x;
		normals[i * 3 + 1] = mesh->mNormals[i].y;
		normals[i * 3 + 2] = mesh->mNormals[i].z;
		if (mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates?
		{
			texCoords[i * 2] = mesh->mTextureCoords[0][i].x;
			texCoords[i * 2 + 1] = mesh->mTextureCoords[0][i].y;
		}
		else
			texCoords[i * 2] = texCoords[i * 2 + 1] = 0.0f;
	}
	// Process indices
	for (GLuint i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (GLuint j = 0; j < face.mNumIndices; j++)
			indicesList.push_back(face.mIndices[j]);
	}
	indices = new int[indicesList.size()];
	indexLength = indicesList.size();
	for (int i = 0; i < (int)indicesList.size(); i++)
		indices[i] = indicesList[i];

	// Process material
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<Texture> diffuseMaps = this->LoadMaterialTextures(material,
			aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(std::pair<TextureType,std::vector<Texture>>
			(TextureType::diffuse,
				diffuseMaps));
		std::vector<Texture> specularMaps = this->LoadMaterialTextures(material,
			aiTextureType_SPECULAR, "texture_specular");
		textures.insert(std::pair<TextureType, std::vector<Texture>>
			(TextureType::specular,
				specularMaps));
	}

	const int BONE_ID_MAXIMUM = 4;
	int boneLength = mesh->mNumVertices * BONE_ID_MAXIMUM;
	int *boneIDs = new int[boneLength];
	std::fill_n(boneIDs, boneLength, -1);
	float *weights = new float[boneLength] {0.0f};
	
	std::map<std::string, Bone*> boneMaps;

	for (int i = 0; i < (int)mesh->mNumBones; i++)
	{
		std::string boneName = mesh->mBones[i]->mName.C_Str();
		if (boneMaps.find(boneName) == boneMaps.end())
		{
			Bone *bone = new Bone();
			bone->index = (int)boneMaps.size();
			boneMaps.insert_or_assign(boneName, bone);
		}

		for (int j = 0; j < (int)mesh->mBones[i]->mNumWeights; j++)
		{
			int vertexID = mesh->mBones[i]->mWeights[j].mVertexId;
			float weight = mesh->mBones[i]->mWeights[j].mWeight;
			glm::mat4 offsetMatrix = glm::make_mat4<float>(mesh->mBones[i]->mOffsetMatrix[0]);
			boneMaps[boneName]->inverseBindPoseMatrix = glm::transpose(offsetMatrix);
			for (int k = 0; k < BONE_ID_MAXIMUM; k++)
			{
				int boneIndex = vertexID * BONE_ID_MAXIMUM + k;
				if (boneIDs[boneIndex] == -1)
				{
					boneIDs[boneIndex] = boneMaps[boneName]->index;
					weights[boneIndex] = weight;
					//Debug::Log("vertex-index:" + std::to_string(boneIndex) + "/bone-index:" + std::to_string(boneMaps[boneName]->index));
					break;
				}
			}
		}
	}

	/*for (int pp = 0; pp < (int)mesh->mNumVertices; pp++)
	{
		glm::vec4 boneIDDebug(boneIDs[pp * 4], boneIDs[pp * 4+ 1], boneIDs[pp * 4 + 2], boneIDs[pp * 4 + 3]);
		glm::vec4 boneWeightDebug(weights[pp * 4], weights[pp * 4 + 1], weights[pp * 4 + 2], weights[pp * 4 + 3]);
		glm::vec3 vertex(vertices[pp * 3], vertices[pp * 3 + 1], vertices[pp * 3 + 2]);
		Debug::Log("vertex: " + std::to_string(vertex.x) + "," + std::to_string(vertex.y) + "," + std::to_string(vertex.z));
		Debug::Log("bone: " + std::to_string(boneIDDebug.x) + "," + std::to_string(boneIDDebug.y) + "," + std::to_string(boneIDDebug.z) + "," + std::to_string(boneIDDebug.w));
		Debug::Log("weight: " + std::to_string(boneWeightDebug.x) + "," + std::to_string(boneWeightDebug.y) + "," + std::to_string(boneWeightDebug.z) + "," + std::to_string(boneWeightDebug.w));
	}*/

	//BasicRenderModel model = this->loader.LoadRenderModel(vertices, vertexLength, indices, indexLength, texCoords, texCoordLength, normals, normalLength);
	BasicRenderModel model = this->loader.LoadRenderModel(vertices, vertexLength, indices, indexLength, texCoords, texCoordLength, normals, normalLength, boneIDs, weights, boneLength);

	glm::mat4 globalInverseTransform = glm::make_mat4<float>(scene->mRootNode->mTransformation[0]);
	globalInverseTransform = glm::inverse(glm::transpose(globalInverseTransform));
	LoadBoneBasicTransform(scene->mAnimations[0], nullptr, scene->mRootNode, boneMaps);
	LoadBoneAnimation(scene, boneMaps);

	MeshModel outputMesh(model, textures);
	outputMesh.SetAnimationInfos(scene->mAnimations[0]->mName.C_Str(), globalInverseTransform, boneMaps, (float)scene->mAnimations[0]->mTicksPerSecond, (float)scene->mAnimations[0]->mDuration);
	return outputMesh;
	//return MeshModel(this->loader.LoadRenderModel(), );
}

void AssimpLoader::ProcessNodeBaiscVersion(aiNode * node, const aiScene * scene, std::vector<BasicRenderModel>& basics)
{
	// Process all the node's meshes (if any)
	for (GLuint i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		basics.push_back(this->ProcessMeshBasicVersion(mesh, scene));
	}
	// Then do the same for each of its children
	for (GLuint i = 0; i < node->mNumChildren; i++)
	{
		this->ProcessNodeBaiscVersion(node->mChildren[i], scene, basics);
	}
}

BasicRenderModel AssimpLoader::ProcessMeshBasicVersion(aiMesh * mesh, const aiScene * scene)
{
	//std::vector<Vertex> vertices;
	float *vertices = new float[mesh->mNumVertices * 3];
	int vertexLength = mesh->mNumVertices * 3;
	float *normals = new float[mesh->mNumVertices * 3];
	int normalLength = mesh->mNumVertices * 3;
	float *texCoords = new float[mesh->mNumVertices * 2];
	int texCoordLength = mesh->mNumVertices * 2;
	std::vector<int> indicesList;
	int *indices;
	int indexLength;

	//std::vector<Texture> textures;
	std::map<TextureType, std::vector<Texture>> textures;
	for (GLuint i = 0; i < mesh->mNumVertices; i++)
	{
		// Process vertex positions, normals and texture coordinates
		vertices[i * 3] = mesh->mVertices[i].x;
		vertices[i * 3 + 1] = mesh->mVertices[i].y;
		vertices[i * 3 + 2] = mesh->mVertices[i].z;
		normals[i * 3] = mesh->mNormals[i].x;
		normals[i * 3 + 1] = mesh->mNormals[i].y;
		normals[i * 3 + 2] = mesh->mNormals[i].z;
		if (mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates?
		{
			texCoords[i * 2] = mesh->mTextureCoords[0][i].x;
			texCoords[i * 2 + 1] = mesh->mTextureCoords[0][i].y;
		}
		else
			texCoords[i * 2] = texCoords[i * 2 + 1] = 0.0f;
	}
	// Process indices
	for (GLuint i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (GLuint j = 0; j < face.mNumIndices; j++)
			indicesList.push_back(face.mIndices[j]);
	}
	indices = new int[indicesList.size()];
	indexLength = indicesList.size();
	for (int i = 0; i < (int)indicesList.size(); i++)
		indices[i] = indicesList[i];

	return this->loader.LoadRenderModel(vertices, vertexLength, indices, indexLength, texCoords, texCoordLength, normals, normalLength);
}

std::vector<Texture> AssimpLoader::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
	std::vector<Texture> textures;
	for (GLuint i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		GLboolean skip = false;
		for (GLuint j = 0; j < texturesLoaded.size(); j++)
		{
			if (texturesLoaded[j] == str)
			{
				skip = true;
				break;
			}
		}
		if (!skip)
		{   // If texture hasn't been loaded already, load it
			std::string filename = std::string(str.C_Str());
			filename = this->directory + '/' + filename;
			textures.push_back(loader.LoadTexture(filename.c_str()));
			this->texturesLoaded.push_back(str);  // Add to loaded textures
		}
	}
	return textures;
}


void AssimpLoader::LoadBoneAnimation(const aiScene* scene, std::map<std::string, Bone*>& boneMap)
{
	const aiAnimation* pAnimation = scene->mAnimations[0];
	for (std::map<std::string, Bone*>::iterator it = boneMap.begin(); it != boneMap.end(); it++)
	{
		for (int channel = 0; channel < (int)pAnimation->mNumChannels; channel++)
		{
			const aiNodeAnim* nodeAnim = pAnimation->mChannels[channel];
			if (it->first == std::string(nodeAnim->mNodeName.C_Str()))
			{
				Bone* currentBone = it->second;
				for (int i = 0; i < (int)nodeAnim->mNumPositionKeys; i++)
				{
					BoneKey key;
					key.time = nodeAnim->mPositionKeys[i].mTime;
					aiVector3D vec = nodeAnim->mPositionKeys[i].mValue;
					key.vector = glm::vec3(vec.x, vec.y, vec.z);
					currentBone->transformKeys.push_back(key);
				}
				for (int i = 0; i < (int)nodeAnim->mNumRotationKeys; i++)
				{
					BoneKey key;
					key.time = nodeAnim->mRotationKeys[i].mTime;
					aiQuaternion quat = nodeAnim->mRotationKeys[i].mValue;
					//key.rotation = glm::quat(quat.x, quat.y, quat.z, quat.w);
					aiMatrix3x3 mat33 = quat.GetMatrix();
					glm::mat3 glmmat33 = glm::make_mat3<float>(mat33[0]);
					key.rotation = glm::quat_cast(glm::transpose(glmmat33));
					glm::mat4 rotMatrix = glm::mat4_cast(key.rotation);
					currentBone->rotationKeys.push_back(key);
				}
				for (int i = 0; i < (int)nodeAnim->mNumScalingKeys; i++)
				{
					BoneKey key;
					key.time = nodeAnim->mScalingKeys[i].mTime;
					aiVector3D vec = nodeAnim->mScalingKeys[i].mValue;
					key.vector = glm::vec3(vec.x, vec.y, vec.z);
					currentBone->scalingKeys.push_back(key);
				}
			}
		}
	}
}

const aiNodeAnim * AssimpLoader::FindNodeAnim(const aiAnimation * animation, std::string nodeName)
{
	for (int i = 0; i < (int)animation->mNumChannels; i++)
		if (animation->mChannels[i]->mNodeName.C_Str() == nodeName)
			return animation->mChannels[i];
	return nullptr;
}

void AssimpLoader::LoadBoneBasicTransform(const aiAnimation* animation, const aiNode* parentNode,const aiNode* childNode, std::map<std::string, Bone*>& boneMap)
{
	std::string nodeName = std::string(childNode->mName.C_Str());
	const aiAnimation* currentAnimation = animation;
	const aiNodeAnim* pNodeAnim = FindNodeAnim(currentAnimation, nodeName);
	if (pNodeAnim != nullptr)
	{
		if (boneMap.find(nodeName) == boneMap.end())
		{
			Bone* bone = new Bone();
			bone->index = (int)boneMap.size();
			bone->inverseBindPoseMatrix = glm::mat4(1.0);
			boneMap.insert_or_assign(nodeName, bone);
		}
	}
	else if (nodeName == "Scene" || nodeName == "Armature")
	{
		if (boneMap.find(nodeName) == boneMap.end())
		{
			Bone* bone = new Bone();
			bone->index = (int)boneMap.size();
			bone->inverseBindPoseMatrix = glm::mat4(1.0);
			boneMap.insert_or_assign(nodeName, bone);
		}
	}
	if (boneMap.find(nodeName) != boneMap.end())
	{
		glm::mat4 transform = glm::make_mat4<float>(childNode->mTransformation[0]);
		boneMap[nodeName]->transform = glm::transpose(transform);
		boneMap[nodeName]->parent = nullptr;
		if (parentNode != nullptr)
		{
			std::string parentNodeName = std::string(parentNode->mName.C_Str());
			if (boneMap.find(parentNodeName) != boneMap.end())
			{
				boneMap[nodeName]->parent = boneMap[parentNodeName];
				boneMap[parentNodeName]->children.push_back(boneMap[nodeName]);
			}
		}
	}

	for (int i = 0; i < (int)childNode->mNumChildren; i++)
	{
		LoadBoneBasicTransform(animation, childNode, childNode->mChildren[i], boneMap);
	}
}