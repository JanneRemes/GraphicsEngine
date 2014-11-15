
#version 150 core

uniform mat4 World;
uniform mat4 View;
uniform mat4 Projection;

in vec3 vPosition;
in vec3 vColor;
in vec2 vTexCoord;

out vec4 fColor;
out vec2 fTexCoord;

void main()
{
	fColor = vec4(vColor, 1.0f);
	fTexCoord = vTexCoord;
	gl_Position = Projection * View * World * vec4(vPosition, 1.0);
}
