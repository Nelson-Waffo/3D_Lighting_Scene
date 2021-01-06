#pragma once

#include <glad/glad.h>
#include <stb/stb_image.h>

class Textures
{
public:
	static void generate_texture(unsigned int & texture, const char* image_path, GLenum format);
};