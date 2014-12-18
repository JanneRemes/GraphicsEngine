
//<VERTEX
#version 150 core

uniform mat4 World;
uniform mat4 View;
uniform mat4 Projection;

in vec3 Position;
in vec4 Normal;
in vec4 Color;
in vec2 UV;

out vec4 FragColor;
out vec2 FragUV;

void main()
{
	FragColor = Color;
	FragUV = UV;
	gl_Position = Projection * View * World * vec4(Position, 1.0);
}

//<FRAGMENT
#version 150 core

uniform sampler2D Texture;

in vec4 FragColor;
in vec2 FragUV;
out vec4 FinalColor;

void main()
{
	FinalColor = FragColor * texture(Texture, FragUV.xy);
}
