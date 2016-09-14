#version 330 core
  
in vec3 position;
in vec2 texCoord;
in vec3 normal;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float atlasesSize;
uniform vec2 atlasesOffset;


out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;
out float Visibility;

const float density = 0.007f;
const float gradient = 1.5f;

void main()
{
    vec4 viewPos = view * model * vec4(position, 1.0);
    gl_Position =  projection * viewPos;
	FragPos = vec3(model * vec4(position, 1.0f));
	Normal = mat3(transpose(inverse(model))) * normal;
	TexCoords = (texCoord / atlasesSize) + atlasesOffset;
	float distance = length(viewPos.xyz);
	Visibility = exp(-pow(distance * density, gradient));
	Visibility = clamp(Visibility, 0.0f, 1.0f);
}