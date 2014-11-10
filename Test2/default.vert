
#version 150 core

uniform mat4 World;
uniform mat4 View;
uniform mat4 Projection;

in vec3 Position;
in vec3 Color;

out vec3 FragColor;

void main()
{
	FragColor = Color;
	gl_Position = Projection * View * World * vec4(Position, 1.0);
}
