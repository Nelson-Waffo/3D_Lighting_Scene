// vertex  shader: called for every vertex in the vertex data
#version 330 core
// passing vertex attributes to the vertex shader
layout (location = 0) in vec3 position;
// texture coordinates
layout(location = 1) in vec2 tCoords;
// normal vector
layout(location = 2) in vec3 aNormal;

// normal vector as output from the v to the f shader
out vec3 normal;

// texture coordinates as inputs to the fragment shader
out vec2 texCoords;

// position vector for the fragment
out vec3 fragPos;

// matrices
// MVP
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
// normal matrix
uniform mat3 normalMatrix;

void main()
{
	gl_Position = projection * view * model * vec4(position.x, position.y, position.z, 1.0);
	// pass the texture coordinates to the fragment shader
	texCoords = tCoords;

	// calculate the fragment position by multiplying it with the model matrix
	fragPos = vec3(model * vec4(position, 1.0));

	// multiply the normal by the normal matrix before passing it to the fragment shader
	normal = normalMatrix * aNormal;
}