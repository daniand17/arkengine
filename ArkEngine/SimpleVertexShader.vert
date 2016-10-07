#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal_modelspace;

out vec2 UV;
out vec3 position_worldspace;
out vec3 normal_cameraspace;
out vec3 eyeDirection_cameraspace;
out vec3 lightDirection_cameraspace;

uniform mat4 P, V, M;

vec3 lightPos_worldspace = vec3(2, 2, 2);

void main()
{
	gl_Position = P * V * M * vec4(vertexPosition_modelspace, 1);
	UV = vertexUV;

	vec3 position_worldspace = ( M * vec4(vertexPosition_modelspace, 1) ).xyz;
	vec3 vertexPos_cameraspace = ( V * M * vec4(vertexPosition_modelspace, 1) ).xyz;

	eyeDirection_cameraspace = vec3(0, 0, 0) - vertexPos_cameraspace;

	vec3 lightPos_cameraspace = ( V * vec4(lightPos_worldspace, 1) ).xyz;
	vec3 lightDirection_cameraspace = lightPos_cameraspace + eyeDirection_cameraspace;

	normal_cameraspace = ( V * M * vec4(vertexNormal_modelspace, 0) ).xyz;
	
	
}
