#version 330 core
#define GLSLIFY 1

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;
out vec4 color;

uniform vec3 viewPos;

// Set Struct Material
struct Material 
{
    sampler2D diffuse0;
    sampler2D specular0;
    float shininess;
};  

uniform Material material;

// Set DirLight
struct DirLight {	
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  

uniform DirLight dirLight;

vec3 CalcDirLight(vec3 normal, vec3 viewDir, vec3 diffuseColor, vec3 specColor, float shininess)
{
    DirLight light = dirLight;
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

// Set PointLight
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

uniform PointLight pointLights[MAXIMUM_POINT_LIGHTS];
uniform int pointLightSize;

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 diffuseColor, vec3 specColor, float shininess)
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

vec3 CalcPointLights(vec3 normal, vec3 fragPos, vec3 viewDir, vec3 diffuseColor, vec3 specColor, float shininess)
{
	vec3 pointColor = vec3(0.0f ,0.0f ,0.0f);
    for(int i = 0; i < pointLightSize; i++)
        pointColor += CalcPointLight(pointLights[i], normal, fragPos, viewDir, diffuseColor ,specColor, shininess);
	return pointColor;
}

// Set Fog
in float Visibility;
uniform vec3 skyColor;

vec4 ProcessFog(vec4 color)
{
	return mix(vec4(skyColor, 1.0f), color, Visibility);
}

void main()
{

	vec3 norm = normalize(Normal);

	vec3 viewDir = normalize(viewPos - FragPos);

	
	vec3 dirColor = CalcDirLight(norm, viewDir, vec3(texture(material.diffuse0, TexCoords))
	,vec3(texture(material.specular0, TexCoords)), material.shininess);

	// Phase 2: Point lights
	vec3 pointColors = CalcPointLights(norm, FragPos, viewDir, vec3(texture(material.diffuse0, TexCoords))
	, vec3(texture(material.specular0, TexCoords)), material.shininess);
	
	color = vec4(dirColor + pointColors, 1.0f);  
	color = ProcessFog(color);
} 
