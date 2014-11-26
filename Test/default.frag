
#version 150 core

uniform sampler2D Texture;

in vec4 FragColor;
in vec2 FragUV;
out vec4 FinalColor;

void main()
{
	FinalColor = FragColor * texture(Texture, FragUV);
}
