#version 330 core

struct MaterialInfo
{
	float ka;
	float kd;
	float ks;
	float shininess;
};

struct LightInfo
{
	vec3 eyePosition;
	vec3 direction;
	vec3 color;
	float power;
};

in vec2 UV;
in vec3 normal_eyespace;
in vec3 position_eyespace;

uniform sampler2D myTextureSampler;
uniform LightInfo lightInfo;

const float shininess = 64.0;
const float screenGamma = 2.2;

out vec4 frag_color;			// Out to the gfx card

void main()
{

	vec3 normal = normalize(normal_eyespace);
	vec3 lightDir = normalize(lightInfo.eyePosition - position_eyespace);
	float lambertian = max(dot(lightDir, normal), 0.0);
	float specular = 0.0;

	if(lambertian > 0.0)
	{
		vec3 viewDir = normalize(-position_eyespace);
		
		vec3 halfDir = normalize(lightDir + viewDir);
		float specAngle = max(dot(halfDir, normal), 0.0);
		specular = pow(specAngle, shininess);
	}
	vec3 diffuseColor = texture(myTextureSampler, UV).rgb;

	vec3 colorLinear =	vec3(0.1, 0.1, 0.1) +
						lambertian * diffuseColor +
						specular * lightInfo.color * lightInfo.power;

	frag_color = vec4(colorLinear, 1.0);
	
}