#version 330 core
// All positions should be half around the origin in ndc.
in vec2 position;
uniform vec2 translate;
uniform mat4 scale;
uniform mat4 rotate;
uniform vec2 screenSize;
uniform vec2 texSize;
out vec2 TexCoords;

void main()
{
	vec4 realPosition = rotate * scale * vec4(position.x, position.y, 0.0f, 1.0f);
	float normX = realPosition.x / (screenSize.x / 2.0f) + translate.x / screenSize.x;
	float normY = realPosition.y / (screenSize.y / 2.0f) + translate.y /screenSize.y;
    gl_Position = vec4(normX, normY, 0.0f, 1.0f);
	float texX = position.x / texSize.x + 0.5f;
	float texY = 1.0f - position.y / texSize.y + 0.5f;
	TexCoords = vec2(texX, texY);
}