#version 330 core

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

uniform DirLight dirLight;

uniform sampler2D diffuse;
uniform vec3 specular;
uniform float shininess;

uniform bool useFakeLighting;

uniform vec3 skyColor;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 diffuseColor, vec3 specColor);

void main()
{
    vec4 currentDiffusePixel = texture(diffuse, TexCoords);
	if(currentDiffusePixel.a < 0.5)
		discard;

	vec3 currentNormal = Normal;
	if(useFakeLighting)
		currentNormal = vec3(1.0f, 1.0f, 1.0f);
	vec3 norm = normalize(currentNormal);

	vec3 viewDir = normalize(viewPos - FragPos);

	vec3 dirColor = CalcDirLight(dirLight, norm, viewDir, vec3(currentDiffusePixel) ,specular);

    //color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
	color = vec4(dirColor , 1.0f);  
	//color = vec4(specular, 1.0f);  
	// fog 
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