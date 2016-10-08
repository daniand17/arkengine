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

layout (location = 0) in vec3 vertexPosition_modelspace;
layout (location = 1) in vec2 vertexUV;
layout (location = 2) in vec3 vertexNormal_modelspace;

out vec3 position_eyespace;
out vec3 normal_eyespace;
out vec2 UV;

uniform LightInfo lightInfo;
uniform mat4 V, M, N, MVP;

void main()
{
	gl_Position = (MVP * vec4(vertexPosition_modelspace, 1.0));
	position_eyespace = (V * M * vec4(vertexPosition_modelspace, 1.0)).xyz;
	normal_eyespace = (N * vec4(vertexNormal_modelspace, 0.0)).xyz;
	UV = vertexUV;
}
