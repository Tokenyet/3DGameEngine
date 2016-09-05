#pragma once
#include "Core.h"
#include "BasicRenderModel.h"
#include "Loader.h"
#include <fstream>
#include <sstream>
class OBJLoader
{
public:
	static BasicRenderModel LoadObjModel(const char* path, Loader &loader);
private:
	static void Split(const std::string &s, char delim, std::vector<std::string> &elems);
	static void ProcessVertex(const std::vector<std::string> vertexData, std::vector<int>& indices,
		std::vector<glm::vec2>& texCoords, std::vector<glm::vec3>& normals,
		float* texCoordsArray, float* normalsArray);
};

