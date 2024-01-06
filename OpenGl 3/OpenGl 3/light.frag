#version 450 core
// the lighting frag
out vec4 fragcolour;

uniform vec4 lightColor;

void main()
{
	fragcolour = lightColor;
}