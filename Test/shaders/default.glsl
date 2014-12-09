
//<VERTEX
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

//<FRAGMENT
#version 150 core

uniform sampler2D Texture;

in vec4 FragColor;
in vec2 FragUV;
out vec4 FinalColor;

void main()
{
	FinalColor = FragColor * texture(Texture, FragUV);
}
