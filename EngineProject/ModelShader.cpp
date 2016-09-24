#include "ModelShader.h"

const char * ModelShader::VERTEX_SHADER = "shader/mesh.vert";
const char * ModelShader::FRAGMENT_SHADER = "shader/mesh.frag";

void ModelShader::BindAttributes()
{
	StaticShader::BindAttributes();
	BindAttribute(VertexAttributeLocationRule::boneID, "boneID");
	BindAttribute(VertexAttributeLocationRule::boneWeight, "boneWeight");
}

ModelShader::ModelShader() : StaticShader(VERTEX_SHADER, FRAGMENT_SHADER)
{
	diffuseCount = 0;
	specularCount = 0;
}

ModelShader::~ModelShader()
{
	this->DeleteProgram();
}

void ModelShader::SetDiffuse(GLuint texture)
{
	glActiveTexture(GL_TEXTURE0 + diffuseCount);
	glBindTexture(GL_TEXTURE_2D, texture);
	std::string diffuse = "material.diffuse" + std::to_string(diffuseCount);
	int loc = GetUniformLocation(diffuse.c_str());
	if (loc == -1) Debug::Log("Diffuse texture Setting Fail.");
	glUniform1i(loc, diffuseCount);
	diffuseCount++;
}

void ModelShader::SetSpecular(GLuint texture)
{
	glActiveTexture(GL_TEXTURE0 + diffuseCount);
	glBindTexture(GL_TEXTURE_2D, texture);
	std::string specular = "material.specular" + std::to_string(specularCount);
	int loc = GetUniformLocation(specular.c_str());
	if (loc == -1) Debug::Log("Specular texture Setting Fail.");
	glUniform1i(loc, diffuseCount);
	diffuseCount++;
	specularCount++;
}


void ModelShader::SetShininess(float shininess)
{
	int loc = GetUniformLocation("material.shininess");
	if (loc == -1) Debug::Log("Material Shininess Setting Fail.");
	glUniform1f(loc, shininess);
}

void ModelShader::SetBoneTransform(int index, glm::mat4 transform)
{
	std::string boneTransform = "boneTransform[" + std::to_string(index) + "]";
	int loc = GetUniformLocation(boneTransform.c_str());
	if (loc == -1) Debug::Log("Bone Transform Setting Fail.");
	glUniformMatrix4fv(loc,1, GL_FALSE, glm::value_ptr(transform));
	//glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
}
