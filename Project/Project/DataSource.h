#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include "Textures.h"
#include <iostream>

using namespace std;

struct Element {
	glm::vec3 translation;
	float angle;
	float scaleX;
	float scaleY;
	float scaleZ;
	unsigned int texture;
	const char* name = "";
};

enum class Data {
	Element, ModelLight, CubeLight, Spider
};

class DataSource
{
private:
	static const char* terrain_name;
public:
	static vector<Element> get_data(Data data);
	static void store_cube_data(unsigned int& vao, unsigned int& vbo);
	static const char* get_terrain();
	static void create_texture(const char* terrain_texture, GLenum format);
};