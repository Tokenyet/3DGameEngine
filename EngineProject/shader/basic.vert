#version 330 core
  
in vec3 position;
in vec2 texCoord;
// uniform mat4 model;
// uniform mat4 view;
// uniform mat4 projection;

out vec2 vout_texCoord;

void main()
{
    //gl_Position =  projection * view * model * vec4(position, 1.0);
	gl_Position =  vec4(position, 1.0);
	vout_texCoord = texCoord;
}