#include "Shader.h"
#include "ResourceManager.h"


// a function to compile shaders
unsigned int compile_shaders(const char* shadercode, GLenum type) 
{
    // create the shader object and return its id
    unsigned int shader = glCreateShader(type);
    // attach the shader to its code
    glShaderSource(shader, 1, &shadercode, NULL);
    // compile the shader code
    glCompileShader(shader);
    // check for compilation errors
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success == 0) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        cout << "failure to compile a shader: " << infoLog << endl;
        glDeleteShader(shader);
    }
    else {
        return shader;
    }
}

// a function used to create the shader program object
unsigned int Shader::get_shader_program(const char* vertex, const char* fragment)
{
    Shaders shaders = ResourceManager::getShadersCode(vertex, fragment);
    const char* vertex_code = shaders.vertexcode.c_str();
    const char* fragment_code = shaders.fragmentscode.c_str();
    // compile shaders
    unsigned int vshader = compile_shaders(vertex_code, GL_VERTEX_SHADER);
    unsigned int fshader = compile_shaders(fragment_code, GL_FRAGMENT_SHADER);
    // create the shader program object
    unsigned int program = glCreateProgram();
    // bind the shaders to the shader program object
    glAttachShader(program, vshader);
    glAttachShader(program, fshader);
    glLinkProgram(program);
    glValidateProgram(program);
    // check for potential program linking errors
    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (success == 0) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        cout << "Failed to link the shader program object: " << infoLog << endl;
        glDeleteProgram(program);
    }
    else {
        return program;
    }
}
