#version 330 core

in vec2 UV;
in vec3 position_worldspace;
in vec3 normal_cameraspace;
in vec3 eyeDirection_cameraspace;
in vec3 lightDirection_cameraspace;

out vec3 color;			// Out to the gfx card

vec3 lightPos_worldspace = vec3(2, 2, 2);


uniform sampler2D myTextureSampler;

void main()
{
	vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
	float lightPower = 500.0f;
	
	vec3 materialDiffuseColor = texture(myTextureSampler, UV).rgb;
	vec3 materialAmbientColor = vec3(0.1, 0.1, 0.1) * materialDiffuseColor;
	vec3 materialSpecularColor = vec3(1.0, 1.0, 1.0);

	float distance = length( lightPos_worldspace - position_worldspace);

	vec3 n = normalize( normal_cameraspace );
	vec3 l = normalize (lightDirection_cameraspace);

	float cosTheta = clamp( dot(n, l), 0, 1);
	
	vec3 eye = normalize(eyeDirection_cameraspace);
	vec3 r = reflect(-l, n);
	
	float cosAlpha = clamp( dot( eye, r ), 0, 1);

	color = materialAmbientColor +
			materialDiffuseColor * lightColor * lightPower * cosTheta +
			materialSpecularColor * lightColor * lightPower * pow(cosAlpha, 5);

}