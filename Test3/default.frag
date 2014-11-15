
#version 150 core

uniform sampler2D Tex;

in vec4 fColor;
in vec2 fTexCoord;

out vec4 FinalColor;

void main()
{
	FinalColor = texture(Tex, fTexCoord) * fColor;
}
