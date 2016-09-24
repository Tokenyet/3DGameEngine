#version 330 core
struct Material 
{
    sampler2D diffuse0;
    sampler2D specular0;
    float shininess;
};  

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
uniform Material material;
uniform Light light;

uniform vec3 skyColor;

void main()
{
	vec3 lightPos = light.position;
    // Ambient
    vec3 ambient = light.ambient * vec3(texture(material.diffuse0, TexCoords));
	
	// Diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);  
	float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse0, TexCoords));

	    // Specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular0, TexCoords));
    //color = vec4(1.0f, 0.5f, 0.2f, 1.0f);

	color = vec4(ambient + diffuse + specular, 1.0f);  
	//color = vec4(specular, 1.0f);  
	color = mix(vec4(skyColor, 1.0f), color, Visibility);
} 