#shader vertex
#version 410 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texcoords;

out vec2 vtexcoords;

uniform mat4 mvp;

void main()
{
	gl_Position = mvp * position;
	vtexcoords = texcoords;
}

#shader fragment
#version 410 core

layout(location = 0) out vec4 color;

in vec2 vtexcoord;

uniform sampler2D uTexture;

void main()
{
	vec4 texcolor = texture(uTexture, vtexcoord);
	color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}