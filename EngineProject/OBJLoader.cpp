#include "OBJLoader.h"



void OBJLoader::Split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss;
	ss.str(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
}
void OBJLoader::ProcessVertex(const std::vector<std::string> vertexData, std::vector<int>& indices,
	std::vector<glm::vec2>& texCoords, std::vector<glm::vec3>& normals,
	float* texCoordsArray, float* normalsArray)
{
	int currentVertexIndex = atoi(vertexData[0].c_str()) - 1;
	int currentTexCoordIndex = atoi(vertexData[1].c_str()) - 1;
	int currentNormalIndex = atoi(vertexData[2].c_str()) - 1;
	// vertex index(position) add in indices
	indices.push_back(currentVertexIndex);
	glm::vec2 currentTexCoord = texCoords[currentTexCoordIndex];
	// vertex index(position) in vertices(positions) is 
	texCoordsArray[currentVertexIndex * 2] = currentTexCoord.x;
	texCoordsArray[currentVertexIndex * 2 + 1] = 1.0f - currentTexCoord.y;
	glm::vec3 currentNormal = normals[currentNormalIndex];
	// same vertex has same normal array index.
	normalsArray[currentVertexIndex * 3] = currentNormal.x;
	normalsArray[currentVertexIndex * 3 + 1] = currentNormal.y;
	normalsArray[currentVertexIndex * 3 + 2] = currentNormal.z;
}


BasicRenderModel OBJLoader::LoadObjModel(const char* path, Loader &loader)
{
	// one vertex has one position, one texCoord ,and one normal.
	// one index represent the index of position in vertices,
	// indices represent the list of index
	std::ifstream inputFileStream(path);
	std::string line;
	// vertex array
	std::vector<glm::vec3> vertices;
	// texture coord array
	std::vector<glm::vec2> texCoords;
	// normal array
	std::vector<glm::vec3> normals;
	std::vector<int> indices;
	float *verticesArray;
	int verticesArrayLength;
	float *texCoordsArray = new float[0];
	int texCoordsArrayLength;
	float *normalsArray = new float[0];
	int normalsArrayLength;
	int *indicesArray;
	int indicesArrayLength;
	bool indexScaning = false;
	// The format in obj file not represent what we read directly,
	// ex. 1000 vertices ,but vertex texCoord and vertex normal are not equal 1000
	// According to indices, normal and vertices are the same size.
	while (std::getline(inputFileStream, line))
	{
		std::vector<std::string> currentLine;
		Split(line, ' ', currentLine);
		if (currentLine[0] == "v")
		{
			glm::vec3 vertex = glm::vec3(
				atof(currentLine[1].c_str()),
				atof(currentLine[2].c_str()),
				atof(currentLine[3].c_str())
			);
			vertices.push_back(vertex);
		}
		else if (currentLine[0] == "vt")
		{
			glm::vec2 texCoord = glm::vec2(
				atof(currentLine[1].c_str()),
				atof(currentLine[2].c_str())
			);
			texCoords.push_back(texCoord);
		}
		else if (currentLine[0] == "vn")
		{
			glm::vec3 normal = glm::vec3(
				atof(currentLine[1].c_str()),
				atof(currentLine[2].c_str()),
				atof(currentLine[3].c_str())
			);
			normals.push_back(normal);
		}
		else if (currentLine[0] == "f")
		{
			if (!indexScaning)
			{
				texCoordsArray = new float[vertices.size() * 2];
				texCoordsArrayLength = vertices.size() * 2;
				normalsArray = new float[vertices.size() * 3];
				normalsArrayLength = vertices.size() * 3;
				indexScaning = true;
			}

			std::vector<std::string> vertex1;
			std::vector<std::string> vertex2;
			std::vector<std::string> vertex3;
			Split(currentLine[1], '/', vertex1);
			Split(currentLine[2], '/', vertex2);
			Split(currentLine[3], '/', vertex3);
			ProcessVertex(vertex1, indices, texCoords, normals, texCoordsArray, normalsArray);
			ProcessVertex(vertex2, indices, texCoords, normals, texCoordsArray, normalsArray);
			ProcessVertex(vertex3, indices, texCoords, normals, texCoordsArray, normalsArray);
		}
	}

	verticesArray = new float[vertices.size() * 3];
	verticesArrayLength = vertices.size() * 3;
	indicesArray = new int[indices.size()];
	indicesArrayLength = indices.size();

	for (int i = 0; i < (int)indices.size(); i++)
		indicesArray[i] = indices[i];

	for (int i = 0; i < (int)vertices.size(); i++)
	{
		verticesArray[i * 3] = vertices[i].x;
		verticesArray[i * 3 + 1] = vertices[i].y;
		verticesArray[i * 3 + 2] = vertices[i].z;
	}

	return loader.LoadRenderModel(verticesArray, verticesArrayLength, indicesArray, indicesArrayLength,
		texCoordsArray, texCoordsArrayLength);
}