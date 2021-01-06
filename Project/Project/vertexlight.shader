#version 330 core

layout(location = 0) in vec3 aPosition;

// matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normalMatrix;

void main()
{
	gl_Position = projection * view * model * vec4(aPosition, 1.0);
}