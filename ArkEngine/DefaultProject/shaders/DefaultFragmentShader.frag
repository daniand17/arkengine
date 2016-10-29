#version 330 core

struct MaterialInfo
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct LightInfo
{
	vec3 eyePosition;
	vec3 color;
};

in vec2 UV;
in vec3 normal_eyespace;
in vec3 position_eyespace;

uniform vec3 viewPosition_eyespace;
uniform LightInfo lightInfo;
uniform MaterialInfo material;

out vec4 frag_color;			// Out to the gfx card

void main()
{
	vec3 ambient = lightInfo.color * material.ambient;

	vec3 norm = normalize(normal_eyespace);
	vec3 lightDir = normalize(lightInfo.eyePosition - position_eyespace);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = lightInfo.color * (diff * material.diffuse);

	vec3 viewDir = normalize(-position_eyespace);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = lightInfo.color * (spec * material.specular);
	
	frag_color = vec4(ambient + diffuse + specular, 1.0);
}