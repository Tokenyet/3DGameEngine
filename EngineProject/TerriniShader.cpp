#include "TerrainShader.h"


const char * TerrainShader::VERTEX_SHADER = "shader/terrian.vert";
const char * TerrainShader::FRAGMENT_SHADER = "shader/terrian.frag";
TerrainShader::TerrainShader() : StaticShader(VERTEX_SHADER, FRAGMENT_SHADER)
{
}

TerrainShader::~TerrainShader()
{
}
