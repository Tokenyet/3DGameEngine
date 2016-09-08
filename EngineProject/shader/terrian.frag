#version 330 core

struct Light 
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};


in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;
in float Visibility;
out vec4 color;

uniform vec3 viewPos;

uniform Light light;

//uniform sampler2D diffuse;
uniform vec3 specular;
uniform float shininess;

uniform vec3 skyColor;

uniform sampler2D backgroundTexture;
uniform sampler2D rTexture;
uniform sampler2D gTexture;
uniform sampler2D bTexture;
uniform sampler2D blendMap;

void main()
{
    // blendmap
	vec4 blendMapColor = texture(blendMap, TexCoords);
	float backTextureWeight = clamp(1.0f - (blendMapColor.r + blendMapColor.g + blendMapColor.b), 0.0f, 1.0f);
	vec2 tileCoords = TexCoords * 40.0f;
	vec4 backgroundTextureColor = texture(backgroundTexture, tileCoords) * backTextureWeight;
	vec4 rTextureColor = texture(rTexture, tileCoords) * blendMapColor.r;
	vec4 gTextureColor = texture(gTexture, tileCoords) * blendMapColor.g;
	vec4 bTextureColor = texture(bTexture, tileCoords) * blendMapColor.b;

	vec3 totalColor = (backgroundTextureColor + rTextureColor + gTextureColor + bTextureColor).xyz;

	vec3 lightPos = light.position;
    // Ambient
    vec3 ambientValue = light.ambient * totalColor;
	
	// Diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);  
	float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuseValue = light.diffuse * diff * totalColor;

	    // Specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specularValue = light.specular * spec * specular;
    //color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
	color = vec4(ambientValue + diffuseValue + specularValue , 1.0f);  
	//color = vec4(specular, 1.0f);  
	color = mix(vec4(skyColor, 1.0f), color, Visibility);
} 