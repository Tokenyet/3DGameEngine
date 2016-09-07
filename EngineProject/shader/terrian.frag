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

uniform sampler2D diffuse;
uniform vec3 specular;
uniform float shininess;

uniform vec3 skyColor;

void main()
{
	vec3 lightPos = light.position;
    // Ambient
    vec3 ambientValue = light.ambient * vec3(texture(diffuse, TexCoords));
	
	// Diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);  
	float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuseValue = light.diffuse * diff * vec3(texture(diffuse, TexCoords));

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