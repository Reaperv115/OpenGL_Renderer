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
uniform sampler2D uTexture;

void main()
{
	vec4 texColor = texture(uTexture, vtexCoord);
	color = texColor;
}