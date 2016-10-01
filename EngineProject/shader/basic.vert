#version 330 core
#define GLSLIFY 1
  
in vec3 position;
in vec3 normal;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec3 FragPos;
out vec3 Normal;

// Set Texture Atlases
uniform float atlasesSize;
uniform vec2 atlasesOffset;

in vec2 texCoord;
out vec2 TexCoords;

void SetTexCoordByAtlases()
{
	TexCoords = (texCoord / atlasesSize) + atlasesOffset;
}

// Set Fog
out float Visibility;

const float density = 0.007f;
const float gradient = 1.5f;

void SetFog(vec4 viewPos)
{
	float distance = length(viewPos.xyz);
	Visibility = exp(-pow(distance * density, gradient));
	Visibility = clamp(Visibility, 0.0f, 1.0f);
}

void main()
{
    vec4 viewPos = view * model * vec4(position, 1.0);
    gl_Position =  projection * viewPos;
	FragPos = vec3(model * vec4(position, 1.0f));
	Normal = mat3(transpose(inverse(model))) * normal;
	SetFog(viewPos);
	SetTexCoordByAtlases();
}