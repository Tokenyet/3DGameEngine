#version 330 core

struct DirLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  

struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

#define MAXIMUM_POINT_LIGHTS 10

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;
in float Visibility;
out vec4 color;

uniform vec3 viewPos;

uniform DirLight dirLight;
uniform PointLight pointLights[MAXIMUM_POINT_LIGHTS];
uniform int pointLightSize;

//uniform sampler2D diffuse;
uniform vec3 specular;
uniform float shininess;

uniform vec3 skyColor;

uniform sampler2D backgroundTexture;
uniform sampler2D rTexture;
uniform sampler2D gTexture;
uniform sampler2D bTexture;
uniform sampler2D blendMap;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 diffuseColor, vec3 specColor);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 diffuseColor, vec3 specColor);

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


	vec3 norm = normalize(Normal);

	vec3 viewDir = normalize(viewPos - FragPos);

	vec3 dirColor = CalcDirLight(dirLight, norm, viewDir, totalColor ,specular);

	vec3 pointColor = vec3(0.0f ,0.0f ,0.0f);
    for(int i = 0; i < pointLightSize; i++)
        pointColor += CalcPointLight(pointLights[i], norm, FragPos, viewDir, totalColor ,specular);  

    //color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
	color = vec4(dirColor + pointColor, 1.0f);  
	//color = vec4(specular, 1.0f);  
	color = mix(vec4(skyColor, 1.0f), color, Visibility);
} 

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 diffuseColor, vec3 specColor)
{
    vec3 lightDir = normalize(-light.direction);
    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    // Combine results
    vec3 ambient  = light.ambient  * diffuseColor;
    vec3 diffuse  = light.diffuse  * diff * diffuseColor;
    vec3 specular = light.specular * spec * specColor;
    return (ambient + diffuse + specular);
} 

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 diffuseColor, vec3 specColor)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    // Attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // Combine results
    vec3 ambient = light.ambient * diffuseColor;
    vec3 diffuse = light.diffuse * diff * diffuseColor;
    vec3 specular = light.specular * spec * specColor;
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}