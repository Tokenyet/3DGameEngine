#version 330 core 
#define MAX_BONES_PER_VERTEX 4

in vec3 position;
in vec2 texCoord;
in vec3 normal;
in ivec4 boneID;
in vec4 boneWeight;

const int MAX_BONES = 100;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 boneTransform[MAX_BONES];

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;
out float Visibility;

const float density = 0.007f;
const float gradient = 1.5f;

mat4 getBoneMatrix(int boneIndex) 
{
    mat4 retMat = mat4(1.0);
    if (boneID[boneIndex] >= 0) {
        retMat = boneTransform[boneID[boneIndex]];
    }
    return retMat;  
}

float getWeight(int boneIndex) 
{
    float res = 0.0;
    if (boneID[boneIndex] >= 0) {
        res = boneWeight[boneIndex];
    }
    return res;
}

uniform int test = 0;

void main()
{
	/*mat4 boneTransformation = mat4(0.0f);
	float totalWeight = 0.0f;
	for (int i = 0; i < MAX_BONES_PER_VERTEX; i++) 
	{
        float weight = getWeight(i);
        boneTransformation += getBoneMatrix(i) * weight;
		totalWeight += weight;
    }
	boneTransformation = boneTransformation / totalWeight;*/

	mat4 boneTransformation = boneTransform[int(boneID[0])] * boneWeight[0];
    boneTransformation += boneTransform[int(boneID[1])] * boneWeight[1];
    boneTransformation += boneTransform[int(boneID[2])] * boneWeight[2];
    boneTransformation += boneTransform[int(boneID[3])] * boneWeight[3];

	/*mat4 boneTransformation = boneTransform[boneID[0]] * boneWeight[0];
    boneTransformation += boneTransform[boneID[1]] * boneWeight[1];
    boneTransformation += boneTransform[boneID[2]] * boneWeight[2];
    boneTransformation += boneTransform[boneID[3]] * boneWeight[3];*/
	//boneTransformation = boneTransform[boneID[test % 4]] * boneWeight[test % 4];

	/*if(boneID[test % 4] == -1)
		boneTransformation = mat4(1.0f);
	else	
		boneTransformation = boneTransform[boneID[test % 4]] * boneWeight[test % 4];*/
	//mat4 boneTransformation = boneTransform[int(boneID[1])] * boneWeight[1];
	/*if(boneWeight[test % 4] >= 0)
		boneTransformation = mat4(float(boneID[test % 4]));*/
	/*boneTransformation = boneTransform[test % MAX_BONES];*/

	vec3 usingPosition = (boneTransformation * vec4(position, 1.0)).xyz;
	/// WTF!!!!! normal 0.0??????
	vec3 usingNormal = (boneTransformation * vec4(normal, 0.0)).xyz;

    vec4 viewPos = view * model * vec4(usingPosition, 1.0);
    gl_Position =  projection * viewPos;
	FragPos = vec3(model * vec4(usingPosition, 1.0f));
	Normal = mat3(transpose(inverse(model))) * usingNormal;
	TexCoords = texCoord;
	float distance = length(viewPos.xyz);
	Visibility = exp(-pow(distance * density, gradient));
	Visibility = clamp(Visibility, 0.0f, 1.0f);
}