#shader vertex
#version 410 core

layout(location = 0) in vec3 position;

out vec3 vtexCoord;

uniform mat4 vp;

void main()
{
	gl_Position = vp * vec4(position, 1.0f);
	vtexCoord = position;
}

#shader fragment
#version 410 core

out vec4 color;

in vec3 vtexCoord;

uniform samplerCube skybox;

void main()
{
	vec4 texColor = texture(skybox, vtexCoord);
	color = texColor;
}