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

	BasicRenderModel model = this->loader.LoadRenderModel(vertices, vertexLength, indices, indexLength, texCoords, texCoordLength, normals, normalLength);
	return MeshModel(model,textures);
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
