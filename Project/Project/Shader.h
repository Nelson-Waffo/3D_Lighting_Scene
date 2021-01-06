#ifndef SHADER_H
#define SHADER_H
#include <glad/glad.h>

class Shader {
public:
	// the shader program object
	unsigned int ID;
	Shader(const char* vertexpath, const char* fragmentpath) {
		ID = get_shader_program(vertexpath, fragmentpath);
	}
private:
	unsigned int get_shader_program(const char*, const char*);
};
#endif // !SHADER_H
