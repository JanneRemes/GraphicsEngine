
#version 150 core

uniform float Alpha;

in vec3 FragColor;
out vec4 FinalColor;

void main()
{
	FinalColor = vec4(FragColor, Alpha);
}
