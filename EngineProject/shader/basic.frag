#version 330 core
in vec2 vout_texCoord;
out vec4 color;

uniform sampler2D diffuse0;

void main()
{
    //color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
	color = texture(diffuse0, vout_texCoord);
} 