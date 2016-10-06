#version 330 core

in vec2 UV;

out vec3 color;			// Out to the gfx card

uniform sampler2D myTextureSampler;

void main()
{
	color = texture( myTextureSampler, UV).rgb;
}