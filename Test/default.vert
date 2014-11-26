
#version 150 core

in vec3 Position;
in vec4 Color;
in vec2 UV;

out vec2 FragUV;
out vec4 FragColor;

void main()
{
	FragUV = UV;
	FragColor = Color;
	gl_Position = vec4(Position, 1.0);
}
