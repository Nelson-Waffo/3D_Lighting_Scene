#include "Textures.h"
#include <iostream>

void Textures::generate_texture(unsigned int& texture, const char* image_path, GLenum format)
{
	// generate the texture object and store its id
	glGenTextures(1, &texture);
	// bind the texture 
	glBindTexture(GL_TEXTURE_2D, texture);
	// configure the texture object
	// wrapping mode: GL_REPEAT: S and T if the coordinates are out of range
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//filtering mode for the texture to determine the colour to associate to a texture coordinate
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// flip the image
	stbi_set_flip_vertically_on_load(true);
	// load the texture image
	int width, height, noColorChannels;
	unsigned char * data = stbi_load(image_path, &width, &height, &noColorChannels, 0);
	// generate the texture image
	if (data) {
		// create a base level of the loaded image
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		// generate other levels of the loaded image
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "The image could not be loaded" << std::endl;
	}
	// release memory once the image has been loaded and associated with the bound texture object
	stbi_image_free(data);

}
