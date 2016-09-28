#version 330 core

in vec2 TexCoords;

uniform sampler2D guiTexture;

out vec4 color;

void main()
{
	
	color = texture(guiTexture, TexCoords);
	//color = vec4(1.0);
}