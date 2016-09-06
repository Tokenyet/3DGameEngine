#version 330 core
  
in vec3 position;
in vec2 texCoord;
in vec3 normal;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

void main()
{
    gl_Position =  projection * view * model * vec4(position, 1.0);
	FragPos = vec3(model * vec4(position, 1.0f));
	Normal = mat3(transpose(inverse(model))) * normal;
	TexCoords = texCoord * 40.0f;
}