#version 330 core

// Gets the colour of the light but to keep consistency with Opengl being american colour is spelt color.
out vec4 fragcolor;

//gets the currentposition.
in vec3 crntPos;
// gets the normal
in vec3 Normal;
// Gets the colour
in vec3 color;
// gets the texture
in vec2 texCoord;



//grabs the textures and decipher which type they are.
uniform sampler2D diffuse0;
uniform sampler2D specular0;
// gets the light colour
uniform vec4 lightColor;
// gets the light position
uniform vec3 lightPos;
//gets the cameraposition
uniform vec3 camPos;


//making the direclight for the application and scene.
vec4 direcLight()
{
	
	float ambient = 0.20f;

	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f));
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	return (texture(diffuse0, texCoord) * (diffuse + ambient) + texture(specular0, texCoord).r * specular) * lightColor;
}



//what we are outputting.
void main()
{
	// outputs final color
	fragcolor = direcLight();
}