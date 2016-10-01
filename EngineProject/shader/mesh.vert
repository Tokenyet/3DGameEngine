#version 330 core 
#define GLSLIFY 1

in vec3 position;
in vec2 texCoord;
in vec3 normal;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;
uniform int test = 0;

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

// Set BoneTransform
#define MAX_BONES_PER_VERTEX 4
in ivec4 boneID;
in vec4 boneWeight;
const int MAX_BONES_1604150559 = 100;
uniform mat4 boneTransform[MAX_BONES_1604150559];

mat4 CalculateBoneTransforms()
{
	mat4 boneTransformation = boneTransform[int(boneID[0])] * boneWeight[0];
    boneTransformation += boneTransform[int(boneID[1])] * boneWeight[1];
    boneTransformation += boneTransform[int(boneID[2])] * boneWeight[2];
    boneTransformation += boneTransform[int(boneID[3])] * boneWeight[3];
	return boneTransformation;
}

void main()
{
	mat4 boneTransformation = CalculateBoneTransforms();
	vec3 usingPosition = (boneTransformation * vec4(position, 1.0)).xyz;
	/// WTF!!!!! normal 0.0??????
	vec3 usingNormal = (boneTransformation * vec4(normal, 0.0)).xyz;

    vec4 viewPos = view * model * vec4(usingPosition, 1.0);
    gl_Position =  projection * viewPos;
	FragPos = vec3(model * vec4(usingPosition, 1.0f));
	Normal = mat3(transpose(inverse(model))) * usingNormal;
	TexCoords = texCoord;
	SetFog(viewPos);
}