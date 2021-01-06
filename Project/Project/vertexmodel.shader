#version 330 core

// input data from the vertex data stored in the VAO
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

// inputs to the fragment shader
out vec2 texCoords;
out vec3 normal;
out vec3 fragPos;

// matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normalMatrix;

void main(void)
{
	gl_Position = projection * view * model * vec4(aPosition, 1.0);
	texCoords = aTexCoords;
	normal = normalMatrix * aNormal;
	fragPos = vec3(model * vec4(aPosition, 1.0));
}
