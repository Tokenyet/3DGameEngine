#include "TerrainShader.h"


const char * TerrainShader::VERTEX_SHADER = "shader/terrian.vert";
const char * TerrainShader::FRAGMENT_SHADER = "shader/terrian.frag";
TerrainShader::TerrainShader() : StaticShader(VERTEX_SHADER, FRAGMENT_SHADER)
{
}

TerrainShader::~TerrainShader()
{
}

void TerrainShader::SetBlendMap(GLuint blendMap)
{
	glActiveTexture(GL_TEXTURE0 + diffuseCount);
	glBindTexture(GL_TEXTURE_2D, blendMap);
	std::string blend = "blendMap";
	int loc = GetUniformLocation(blend.c_str());
	if (loc == -1) Debug::Log("Blend Map Setting Fail.");
	glUniform1i(loc, diffuseCount);
	diffuseCount++;
}

void TerrainShader::SetTerrainTextures(TerrainTexturePack pack)
{
	glActiveTexture(GL_TEXTURE0 + diffuseCount);
	glBindTexture(GL_TEXTURE_2D, pack.GetTextureBackground().GetID());
	std::string background = "backgroundTexture";
	int loc = GetUniformLocation(background.c_str());
	if (loc == -1) Debug::Log("background texture Setting Fail.");
	glUniform1i(loc, diffuseCount);
	diffuseCount++;

	glActiveTexture(GL_TEXTURE0 + diffuseCount);
	glBindTexture(GL_TEXTURE_2D, pack.GetTextureBlue().GetID());
	std::string blue = "bTexture";
	loc = GetUniformLocation(blue.c_str());
	if (loc == -1) Debug::Log("blue texture Setting Fail.");
	glUniform1i(loc, diffuseCount);
	diffuseCount++;

	glActiveTexture(GL_TEXTURE0 + diffuseCount);
	glBindTexture(GL_TEXTURE_2D, pack.GetTextureRed().GetID());
	std::string red = "rTexture";
	loc = GetUniformLocation(red.c_str());
	if (loc == -1) Debug::Log("red texture Setting Fail.");
	glUniform1i(loc, diffuseCount);
	diffuseCount++;

	glActiveTexture(GL_TEXTURE0 + diffuseCount);
	glBindTexture(GL_TEXTURE_2D, pack.GetTextureGreen().GetID());
	std::string green = "gTexture";
	loc = GetUniformLocation(green.c_str());
	if (loc == -1) Debug::Log("green texture Setting Fail.");
	glUniform1i(loc, diffuseCount);
	diffuseCount++;
}
