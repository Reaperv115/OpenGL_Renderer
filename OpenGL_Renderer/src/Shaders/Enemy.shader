#shader vertex
#version 410 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord; 

out vec2 vtexCoord;

uniform mat4 mvp;

void main()
{
	gl_Position = mvp * position;
	vtexCoord = texCoord;
}

#shader fragment
#version 410 core

layout(location = 0) out vec4 color;

in vec2 vtexCoord;

uniform vec4 uColor;

void main()
{
	color = uColor;
}