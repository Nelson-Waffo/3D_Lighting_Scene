#include "DataSource.h"

const char* DataSource::terrain_name = "terrain";

// texture objects
unsigned int grass_texture;
unsigned int box_texture;

void DataSource::create_texture(const char* terrain_texture, GLenum format)
{
	static bool create_box_once = false;
	// load and create a texture
    // create a variable to store the id of the texture object
	Textures::generate_texture(grass_texture, terrain_texture, format); // zgrass is also good
	if (!create_box_once) {
		Textures::generate_texture(box_texture, "box.png", GL_RGBA);
		create_box_once = true;
	}
}

// a function which returns the name of the terrain
const char* DataSource::get_terrain()
{
	return terrain_name;
}

// a function which returns data
vector<Element> DataSource::get_data(Data data)
{
	// data structure for the lights
	vector<Element> cubelights = {
		// lower left light
		{glm::vec3(-250.0f, 47.0f, 175.0f), 0.0f, 4.0, 4.0, 4.0, 0}, // 0
		// upper right light
		{glm::vec3(120.0f, 39.0f, -250.0f), 0.0f, 4.0, 4.0, 4.0, 0}, // 2
		// flash light
		{glm::vec3(0.0, 0.0, 0.0), 0.0f, 0.0, 0.0, 0.0, 0} // 4
	};
	vector<Element> modellights = {
		// lower right light // 
        {glm::vec3(260.0f, 39.0f, 175.0f), 0.0f, 4.0, 4.0, 4.0, 0}, // 3
		// flash light
		{glm::vec3(0.0, 0.0, 0.0), 0.0f, 0.0, 0.0, 0.0, 0}, // 4
	};

	// spider data
	vector<Element> spiders = {
		{glm::vec3(220.0, 2.0, 220.0), 45.0f, 5.0, 5.0, 5.0, 0},
		{glm::vec3(210.0, 2.0, 160.0), -55.0f, 6.0, 6.0, 6.0, 0},
		{glm::vec3(190.0, 8.0, 195.0), 65.0f, 7.0, 7.0, 7.0, 1},
		{glm::vec3(225.0, 6.0, 180.0), -50.0f, 4.0, 4.0, 4.0, 1}
	};

	// data structure for elements on the terrain
	vector<Element> elements = {
		// the terrain
		{glm::vec3(0.0f, 0.0f, 0.0f), 0.0f, 500.0f, 4.0f, 500.0f, grass_texture, terrain_name},
		// wooden boxes in the center of scene
		{glm::vec3(0.0f, 4.0f, 0.0f), 0.0f, 4.0, 4.0, 4.0, box_texture},
		{glm::vec3(0.0f, 8.0f, 0.0f), 0.0f, 4.0, 4.0, 4.0, box_texture},
		{glm::vec3(0.0f, 12.0f, 0.0f), 0.0f, 4.0, 4.0, 4.0, box_texture},
		{glm::vec3(0.0f, 16.0f, 0.0f), 0.0f, 4.0, 4.0, 4.0, box_texture},

		// wooden boxes at the lower right edge of the scene
		{glm::vec3(248.0f, 4.0f, 248.0f), 0.0f, 4.0, 4.0, 4.0, box_texture},
		{glm::vec3(248.0f, 8.0f, 248.0f), 0.0f, 4.0, 4.0, 4.0, box_texture},
		{glm::vec3(248.0f, 12.0f, 248.0f), 0.0f, 4.0, 4.0, 4.0, box_texture},
		{glm::vec3(248.0f, 16.0f, 248.0f), 0.0f, 4.0, 4.0, 4.0, box_texture},

		// wooden boxes at the lower left edge of the scene
		{glm::vec3(-248.0f, 4.0f, 248.0f), 0.0f, 4.0, 4.0, 4.0, box_texture},
		{glm::vec3(-248.0f, 8.0f, 248.0f), 0.0f, 4.0, 4.0, 4.0, box_texture},
		{glm::vec3(-248.0f, 12.0f, 248.0f), 0.0f, 4.0, 4.0, 4.0, box_texture},
		{glm::vec3(-248.0f, 16.0f, 248.0f), 0.0f, 4.0, 4.0, 4.0, box_texture},

		// wooden boxes at the top left corner of the scene
		{glm::vec3(-248.0f, 4.0f, -248.0f), 0.0f, 4.0, 4.0, 4.0, box_texture},
		{glm::vec3(-248.0f, 8.0f, -248.0f), 0.0f, 4.0, 4.0, 4.0, box_texture},
		{glm::vec3(-248.0f, 12.0f, -248.0f), 0.0f, 4.0, 4.0, 4.0, box_texture},
		{glm::vec3(-248.0f, 16.0f, -248.0f), 0.0f, 4.0, 4.0, 4.0, box_texture},

		// wooden boxes at the top right corner of the scene
		{glm::vec3(248.0f, 4.0f, -248.0f), 0.0f, 4.0, 4.0, 4.0, box_texture},
		{glm::vec3(248.0f, 8.0f, -248.0f), 0.0f, 4.0, 4.0, 4.0, box_texture},
		{glm::vec3(248.0f, 12.0f, -248.0f), 0.0f, 4.0, 4.0, 4.0, box_texture},
		{glm::vec3(248.0f, 16.0f, -248.0f), 0.0f, 4.0, 4.0, 4.0, box_texture},

		// boxes in the lower left corner
		{glm::vec3(-200.0f, 4.5f, 200.0f), 0.0f, 5.0, 5.0, 5.0, box_texture},
		{glm::vec3(-200.0f, 4.5f, 165.0f), 0.0f, 5.0, 5.0, 5.0, box_texture},
		{glm::vec3(-165.0f, 4.5f, 200.0f), 0.0f, 5.0, 5.0, 5.0, box_texture},
		{glm::vec3(-165.0f, 4.5f, 165.0f), 0.0f, 5.0, 5.0, 5.0, box_texture},
		{glm::vec3(-190.0f, 30.5f, 166.0f), -55.0f, 5.0, 5.0, 5.0, box_texture},
		{glm::vec3(-175.0f, 32.5f, 175.0f),  45.0f, 5.0, 5.0, 5.0, box_texture},
		{glm::vec3(-200.0f, 20.5f, 188.0f), -60.0f, 5.0, 5.0, 5.0, box_texture},
		{glm::vec3(-160.0f, 23.5f, 202.0f),  57.0f, 5.0, 5.0, 5.0, box_texture},

		// boxes in the upper right corner
		{glm::vec3(100.0f, 5.0f, -200.0f), 0.0f, 6.0, 6.0, 6.0, box_texture},
		{glm::vec3(105.0f, 5.0f, -150.0f), 0.0f, 6.0, 6.0, 6.0, box_texture},
		{glm::vec3(140.0f, 5.0f, -199.0f), 0.0f, 6.0, 6.0, 6.0, box_texture},
		{glm::vec3(145.0f, 5.0f, -145.0f), 0.0f, 6.0, 6.0, 6.0, box_texture},
		{glm::vec3(125.0f, 20.5f, -181.0f),  65.0f, 6.0, 6.0, 6.0, box_texture},
		{glm::vec3(93.0f, 28.5f, -163.0f), -55.0f, 6.0, 6.0, 6.0, box_texture},
		{glm::vec3(115.0f, 27.5f, -188.0f),  55.0f, 6.0, 6.0, 6.0, box_texture},
		{glm::vec3(143.0f, 28.5f, -155.0f),  -62.0f, 6.0, 6.0, 6.0, box_texture}
	};

	if (data == Data::Element) {
		return elements;
	}
	else if (data == Data::CubeLight) {
		return cubelights;
	}
	else if (data == Data::ModelLight) {
		return modellights;
	}
	else if (data == Data::Spider) {
		return spiders;
	}
}

// a function which stores cube data in the gpu's memory
void DataSource::store_cube_data(unsigned int& vao, unsigned int& vbo)
{
	// cube data to be stored in the gpu's memory
	// array of vertices for creating a cube
	float vertices[] = {
		// vertex position   //texcoord  // normal vectors
	   -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f,  0.0f
	};

	glGenVertexArrays(1, &vao);
	// bind it
	glBindVertexArray(vao);
	// 1 vbo
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	// store the data in the gpu's memory
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
	// data is now on the gpu's memmory
	// tell opengl how to interpret the data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(0 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// normals
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);
}