/****** my lovely garbage ****/

/*
// a function which returns data
vector<Element> get_data(Data data)
{
	// load and create a texture
	// create a variable to store the id of the texture object
	unsigned int grass_texture;
	Texture::generate_texture(grass_texture, "gold.jpg", GL_RGB); // zgrass is good
	unsigned int box_texture;
	Texture::generate_texture(box_texture, "box.png", GL_RGBA);

	// data structure for the lights
	vector<Element> lights = {
		// lower left light
		{glm::vec3(-250.0f, 47.0f, 175.0f), 0.0f, 4.0, 4.0, 4.0, 0}, // 0
		// upper left light
		{glm::vec3(-180.0f, 47.0f, -250.0f), 0.0f, 4.0, 4.0, 4.0, 0}, // 1
		// upper right light
		{glm::vec3(120.0f, 39.0f, -250.0f), 0.0f, 4.0, 4.0, 4.0, 0}, // 2
		// lower right light
		{glm::vec3(250.0f, 39.0f, 175.0f), 0.0f, 4.0, 4.0, 4.0, 0}, // 3
		// flash light
		{camera.Position, 0.0f, 0.0, 0.0, 0.0, 0} // 4
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
	else if (data == Data::Light) {
		return lights;
	}
}

// a function which stores cube data in the gpu's memory
void store_cube_data(unsigned int& vao, unsigned int& vbo)
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
*/

// camera movement

//move_camera(window, cameraPos, cameraFront);
// cameraPos + cameraFront // ensures that however we move the camera still looks in the target direction
// view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

// components
/*glm::vec3 cameraPos = glm::vec3(250.0, 10.0, 270.0);
glm::vec3 cameraFront = glm::vec3(0.0, 0.0, -1.0);
glm::vec3 cameraUp = glm::vec3(0.0, 1.0, 0.0);*/

/*
// enum class for camera direction
enum class Direction {
	Front, Back
};

// a function used to move the camera
void move_camera(GLFWwindow* window, glm::vec3& cameraPos, glm::vec3& cameraFront)
{

	static Direction cameraDirection = Direction::Front;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		if (cameraDirection == Direction::Front)
		{
			cameraPos.z -= 0.01f;
		}
		else
		{
			cameraPos.z += 0.01f;
		}

	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		if (cameraDirection == Direction::Front)
		{
			cameraPos.z += 0.01f;
		}
		else
		{
			cameraPos.z -= 0.01f;
		}
	}

	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		if (cameraDirection == Direction::Front)
		{
			cameraPos.x -= 0.01f;
		}
		else
		{
			cameraPos.x += 0.01f;
		}
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		if (cameraDirection == Direction::Front)
		{
			cameraPos.x += 0.01f;
		}
		else
		{
			cameraPos.x -= 0.01f;
		}
	}
	else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_RELEASE) {
			// toggle the direction
			cameraDirection = (cameraDirection == Direction::Front) ? Direction::Back : Direction::Front;
			cameraFront.z *= -1;
		}
	}

}
*/

// terrain
	// terrain properties

	/*glm::vec3 terrain_position = glm::vec3(0.0, 0.0, 0.0);
	float terrain_scale = 10 * 50;
	float terrain_angle = 0.0f;
	// position the cube in the world
	model = glm::translate(model, terrain_position);
	model = glm::rotate(model, glm::radians(terrain_angle), glm::vec3(1.0, 0.0, 0.0));
	 model = glm::scale(model, glm::vec3(terrain_scale, 4.0, terrain_scale));
	 glUniformMatrix4fv(glGetUniformLocation(shader1.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));*/

	 /*
		 // randomize the rotation
		 // generate a random number between 0 and 99
		 random = rand() % 100;
		 // adjust the rotations
		 if (random % 3 == 0) {
			 dir = -1.0;
			 rotationSpeed = 0.7;
			 bend = 1.0;
		 }
		 else {
			 dir = 1.0;
			 rotationSpeed = 0.4;
			 bend = 0.0;
		 }
	 */

	 /*else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		 static float lastTime = 0;
		 // toggle the yaw value per request but every 5 seconds min
		 if (glfwGetTime() - lastTime > 5.0) {
			 camera.Yaw *= -1;
			 lastTime = glfwGetTime();
		 }
	 }*/

	 // void move_camera(GLFWwindow*, glm::vec3&, glm::vec3&);

	 /* data structures */
	 // structure of an element in the scene
	 /*
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
		 Element, Light
	 };
	 const char* terrain_name = "terrain";
	 */

	 // feed the grass uniform sampler2D object in the fragment shader of the terrain
	 //glUniform1i(glGetUniformLocation(cubeshader.ID, SAMPLER2D1), 0);
	 // void store_cube_data(unsigned int&, unsigned int&);
	 // vector<Element> get_data(Data);
	 /*end of data structures*/

		 //object.Draw(modelshader);
		 // structure for models
		 //multimap<Model, Element> models;
		 //models.insert(pair<Model, Element>(object, { glm::vec3(0.0, 0.0, 0.0), 45.0, 5.0, 5.0, 5.0, 0 }));
		 // models[object] = {glm::vec3(0.0, 0.0, 0.0), 45.0, 5.0, 5.0, 5.0, 0};

			 // inner cutoff:12.5 and outer cutoff: 17.5
			 //glUniform1f(glGetUniformLocation(cubeshader.ID, "lights[2].cutoff"), glm::cos(glm::radians(12.5f)));
			 //glUniform1f(glGetUniformLocation(cubeshader.ID, "lights[2].outercutoff"), glm::cos(glm::radians(17.5f)));


			 //glUniform3fv(glGetUniformLocation(modelshader.ID, "lights[1].position"), 1, glm::value_ptr(modellights[0].translation));

			 //glUniform1f(glGetUniformLocation(modelshader.ID, "lights[1].cutoff"), glm::cos(glm::radians(12.5f)));
			 //glUniform1f(glGetUniformLocation(modelshader.ID, "lights[1].outercutoff"), glm::cos(glm::radians(17.5f)));


				 /*model = glm::mat4(1.0);
				 model = glm::translate(model, iter->translation);
				 model = glm::rotate(model, dir * (rotationSpeed) * (float)(glfwGetTime()) * glm::radians(iter->angle), glm::vec3(1.0, bend, 0.0));
				 model = glm::scale(model, glm::vec3(iter->scaleX, iter->scaleY, iter->scaleZ));
				 glUniformMatrix4fv(glGetUniformLocation(cubeshader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
				 // normal matrix to the fragment shader
				 normalMatrix = glm::mat3(glm::transpose(glm::inverse(model)));
				 glUniformMatrix3fv(glGetUniformLocation(cubeshader.ID, "normalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));*/
				 /*model = glm::mat4(1.0);
	 model = glm::translate(model, iter->translation);
	 model = glm::rotate(model, glm::radians(iter->angle), glm::vec3(1.0, 0.0, 0.0));
	 model = glm::scale(model, glm::vec3(iter->scaleX, iter->scaleY, iter->scaleZ));
	 glUniformMatrix4fv(glGetUniformLocation(lightshader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));*/
	 /*model = glm::mat4(1.0);
	 model = glm::translate(model, iter->translation);
	 model = glm::rotate(model, glm::radians(iter->angle), glm::vec3(1.0, 0.0, 0.0));
	 model = glm::scale(model, glm::vec3(iter->scaleX, iter->scaleY, iter->scaleZ));
	 glUniformMatrix4fv(glGetUniformLocation(lightshader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));*/

	 /*model = glm::mat4(1.0);
	 model = glm::translate(model, iter->translation);
	 model = glm::rotate(model, dir * (rotationSpeed) * (float)(glfwGetTime()) * glm::radians(iter->angle), glm::vec3(iter->texture, 1.0, 0.0));
	 model = glm::scale(model, glm::vec3(iter->scaleX, iter->scaleY, iter->scaleZ));
	 glUniformMatrix4fv(glGetUniformLocation(modelshader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
	 // normal matrix to the fragment shader
	 normalMatrix = glm::mat3(glm::transpose(glm::inverse(model)));
	 glUniformMatrix3fv(glGetUniformLocation(modelshader.ID, "normalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));*/

	 //if (i % 2 != 0) continue; // != display lower left and upper right lights; == display upper left and lower right lights

		 // upper left light
		 //{glm::vec3(-180.0f, 47.0f, -250.0f), 0.0f, 4.0, 4.0, 4.0, 0} // 1

	/*else if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
		DataSource::create_texture(gold_terrain, GL_RGB);
	}*/

	 /*end of garbage*/