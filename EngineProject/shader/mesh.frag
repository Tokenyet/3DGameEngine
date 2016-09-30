#version 330 core
struct Material 
{
    sampler2D diffuse0;
    sampler2D specular0;
    float shininess;
};  

struct DirLight {
    vec3 direction;
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
uniform Material material;
uniform DirLight dirLight;

uniform vec3 skyColor;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 diffuseColor, vec3 specColor, float shininess);


void main()
{

	vec3 norm = normalize(Normal);

	vec3 viewDir = normalize(viewPos - FragPos);

	vec3 dirColor = CalcDirLight(dirLight, norm, viewDir, vec3(texture(material.diffuse0, TexCoords))
	, vec3(texture(material.specular0, TexCoords)), material.shininess);

	color = vec4(dirColor, 1.0f);  
	//color = vec4(specular, 1.0f);  
	color = mix(vec4(skyColor, 1.0f), color, Visibility);
	//color = vec4((norm.x + 1.0f) / 2.0f, (norm.y + 1.0f) / 2.0f, (norm.z + 1.0f) / 2.0f, 1.0f);  
	//color = vec4((norm.x + 1.0f) / 2.0f, 0, 0, 1.0f);  
} 

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 diffuseColor, vec3 specColor, float shininess)
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