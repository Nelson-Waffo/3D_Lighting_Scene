/*3D Lighting Scene - The Genesis: In this scene, lighting effects are implemented on a surface.
This includes: - Basic lighting: where ambient light, diffuse light and specular light are combined.
               - Lighting maps: a diffuse map is used to set the diffuse color for each individual fragment. 
			   a specular map to define the specular intensity for each part of an object. Wooden parts of an object have 
			   no specular highlights, whilst steel part has stronger specular intensities.
			   - Spotlight: a light which shoots light rays in a specific direction. the spot light has an inner and outer cone.
			   the outer cone gradually dims the light from the inner cone to the edges of the outer cone.
*/

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"
#include "Textures.h"
#include "Camera.h"
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <string>
#include "DataSource.h"
#include "model.h"

using namespace std;

/*constants and global variables*/
bool show_gun = true;
//global path for models
string path = "C:/Users/nelso/Documents/ComputerScience/Semester-7/Computer_Graphics/CG_Course_2020/Rehearsal_OpenGL/Scene3D/models";
//global variables for rotations
float bend = 1.0;
float rotationSpeed = 0.5f;
float dir = 1.0f;
// window dimensions
const unsigned int WIDTH = 1200;
const unsigned int HEIGHT = 800;
// shader code
const char* fragment_cube_path = "fragmentcube.shader";
const char* vertex_cube_path = "vertexcube.shader";
const char* vertex_light_path = "vertexlight.shader";
const char* fragment_light_path = "fragmentlight.shader";
const char* vertex_model_path = "vertexmodel.shader";
const char* fragment_model_path = "fragmentmodel.shader";
// textures: specular and diffuse maps
const char* Diffuse = "material.diffuse";
const char* Specular = "material.specular";
const char* Shininess = "material.shininess";
// flashlight
const char* flashlight = "flashlight";
// terrain texture
const char* gold_terrain = "gold.jpg";
const char* grass_terrain = "zgrass.png";
// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;
// camera object
Camera camera(glm::vec3(0.0, 10.0, 270.0));
float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;
bool firstMouse = true;
/*end of constants and global variables*/

float angular = 0.0f;

/****function prototypes*****/
bool initialise(GLFWwindow*&);
void resize_window(GLFWwindow*, int, int);
void process_events(GLFWwindow*);
void process_camera(GLFWwindow*);
void mouse_callback(GLFWwindow*, double, double);
void scroll_callback(GLFWwindow*, double, double);
void compute_model(glm::mat4& model, glm::vec3, float, float, float, float, float, unsigned int, glm::mat3&, bool);
void process_terrain(GLFWwindow*);
void process_flashlight(GLFWwindow*, unsigned int, unsigned int);
/*end of prototypes*/

int main()
{
	// initialise GLFW
	GLFWwindow* window;
	if (!initialise(window)) {
		return -1;
	}

	// opengl functions can be used. first inform open of the size of the window 
	glViewport(0, 0, WIDTH, HEIGHT);
	// update opengl each time the user resizes the window: through a callback function
	glfwSetFramebufferSizeCallback(window, resize_window);

	// enable the depth buffer for depth testing: if a fragment is in front of another fragment it overwrites that other fragment
	// if it is behind, it gets discarded
	glEnable(GL_DEPTH_TEST);

	// store cube data in the gpu's memory for the vertex and fragment shaders
	unsigned int vao;
	unsigned int vbo;
	DataSource::store_cube_data(vao, vbo);

	// load and create a texture
    // create a variable to store the id of the texture object
	unsigned int spec_texture;
	Textures::generate_texture(spec_texture, "specular_map.png", GL_RGBA);

	// compile the shaders and create a shader program object
	Shader cubeshader(vertex_cube_path, fragment_cube_path);
	Shader lightshader(vertex_light_path, fragment_light_path);
	Shader modelshader(vertex_model_path, fragment_model_path);

	/* loading models: spider, airplane */
	string fullpath = path + "/spiderman-scene-obj/spiderman-scene.obj";
	Model spider(fullpath);
	fullpath = path + "/us-c-130-hercules-airplane-obj/us-c-130-hercules-airplane.obj";
	Model airplane(fullpath);
	fullpath = path + "/mp5k/mp5k.obj";
	Model gun(fullpath);
	fullpath = path + "/incredible-hulk-obj/incredible-hulk.obj";
	Model hulk(fullpath);
	fullpath = path + "/dragon-obj/dragon.obj";
	Model dragon(fullpath);
	fullpath = path + "/stol-obj/stol.obj";
	Model chairs(fullpath);
	fullpath = path + "/fixed-opem-sim-bead-model-obj/fixed-opem-sim-bead-model.obj";
	Model bed(fullpath);
	fullpath = path + "/house-obj/house.obj";
	Model house(fullpath);
	fullpath = path + "/audioptimised02-obj/audioptimised02.obj";
	Model car(fullpath);
	fullpath = path + "/ferrari-f1-race-car-obj/ferrari-f1-race-car.obj";
	Model ferrari(fullpath);
	fullpath = path + "/house-but-the-thief-poked-1-window-untiene-obj/house-but-the-thief-poked-1-window-untiene.obj";
	Model brokenhouse(fullpath);
	/*end of loading models*/
    
	// textures
	glUseProgram(cubeshader.ID);
	// diffuse map texture: texture bound to texture unit 0
	glUniform1i(glGetUniformLocation(cubeshader.ID, Diffuse), 0);
	// specular map texture: texture bound to texture unit 1
	glUniform1i(glGetUniformLocation(cubeshader.ID, Specular), 1);
	// shininess
	glUniform1f(glGetUniformLocation(cubeshader.ID, Shininess), 32);

	// matrices
	// projection matrix: perspective matrix
	glm::mat4 projection = glm::perspective(camera.Zoom, (float)WIDTH / (float)HEIGHT, 0.1f, 300.0f);
	glUniformMatrix4fv(glGetUniformLocation(cubeshader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	// view matrix
	glm::mat4 view = glm::mat4(1.0);
	// model matrix
	glm::mat4 model = glm::mat4(1.0);
	// normal matrix
	glm::mat3 normalMatrix;

	// generate the textures and attached them texture objects
	DataSource::create_texture(gold_terrain, GL_RGB);

	// display data
	// data structure for the lights
	vector<Element> cubelights = DataSource::get_data(Data::CubeLight);
	vector<Element> modellights = DataSource::get_data(Data::ModelLight);
	// data structure for elements (boxes) on the terrain
	vector<Element> elements = DataSource::get_data(Data::Element);
	// get data from spiders
	vector<Element> spiders = DataSource::get_data(Data::Spider);

	/* lighting maps*/
	// pass the light positions and other data to the fragment shader
	string temp;
	glm::vec3 light_colour = glm::vec3(1.0);
	glUseProgram(cubeshader.ID);
	// deactivate the flashlight
	glUniform1i(glGetUniformLocation(cubeshader.ID, flashlight), 1);
	for (int i = 0; i < cubelights.size(); ++i) {
			temp = "lights[" + to_string(i) + "].position";
			glUniform3fv(glGetUniformLocation(cubeshader.ID, temp.c_str()), 1, glm::value_ptr(cubelights[i].translation));
			temp = "lights[" + to_string(i) + "].ambient";
			glUniform3fv(glGetUniformLocation(cubeshader.ID, temp.c_str()), 1, glm::value_ptr(0.2f * light_colour));
			temp = "lights[" + to_string(i) + "].diffuse";
			glUniform3fv(glGetUniformLocation(cubeshader.ID, temp.c_str()), 1, glm::value_ptr(0.9f * light_colour));
			temp = "lights[" + to_string(i) + "].specular";
			glUniform3fv(glGetUniformLocation(cubeshader.ID, temp.c_str()), 1, glm::value_ptr(0.9f * light_colour));

			 temp = "lights[" + to_string(i) + "].cutoff";
			glUniform1f(glGetUniformLocation(cubeshader.ID, temp.c_str()), glm::cos(glm::radians(12.5f)));
			temp = "lights[" + to_string(i) + "].outercutoff";
			glUniform1f(glGetUniformLocation(cubeshader.ID, temp.c_str()), glm::cos(glm::radians(17.5f)));

			// attenuation components
			temp = "lights[" + to_string(i) + "].constant";
			glUniform1f(glGetUniformLocation(cubeshader.ID, temp.c_str()), 1.0);
			temp = "lights[" + to_string(i) + "].lineare";
			glUniform1f(glGetUniformLocation(cubeshader.ID, temp.c_str()), 0.0014);
			temp = "lights[" + to_string(i) + "].quadratic";
			glUniform1f(glGetUniformLocation(cubeshader.ID, temp.c_str()), 0.000007);
	}
	glUseProgram(0);

	glUseProgram(modelshader.ID);
	// deactivate the flashlight
	glUniform1i(glGetUniformLocation(modelshader.ID, flashlight), 1);
	for (int j = 0; j < modellights.size(); ++j) {
			temp = "lights[" + to_string(j) + "].colour";
			glUniform3fv(glGetUniformLocation(modelshader.ID, temp.c_str()), 1, glm::value_ptr(light_colour));
			// inner cutoff:12.5 and outer cutoff: 17.5
			temp = "lights[" + to_string(j) + "].cutoff";
			glUniform1f(glGetUniformLocation(modelshader.ID, temp.c_str()), glm::cos(glm::radians(12.5f)));
			temp = "lights[" + to_string(j) + "].outercutoff";
			glUniform1f(glGetUniformLocation(modelshader.ID, temp.c_str()), glm::cos(glm::radians(17.5f)));
			// attenuation components
			temp = "lights[" + to_string(j) + "].constant";
			glUniform1f(glGetUniformLocation(modelshader.ID, temp.c_str()), 1.0);
			temp = "lights[" + to_string(j) + "].lineare";
			glUniform1f(glGetUniformLocation(modelshader.ID, temp.c_str()), 0.0014); // 0.0022
			temp = "lights[" + to_string(j) + "].quadratic";
			glUniform1f(glGetUniformLocation(modelshader.ID, temp.c_str()), 0.000007);// 0.0000019
	}
	glUseProgram(0);
	// remove the flashlight because it does not need to be displayed
	cubelights.pop_back();
	modellights.pop_back();
	/*end of lighting maps*/
	// render loop
	while (glfwWindowShouldClose(window) != true)
	{
		// per-frame time logic
        // --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		// process window events
		process_events(window);
		// change texture texture on demand
		process_terrain(window);
		// interact with the flashlight
		process_flashlight(window, cubeshader.ID, modelshader.ID);

		// clearing colour
		glClearColor(0.0, 0.0, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(cubeshader.ID);
		glBindVertexArray(vao);
		// moving the camera: adjust the camera position
		process_camera(window);
		view = camera.GetViewMatrix();
		glUniformMatrix4fv(glGetUniformLocation(cubeshader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		// pass the camera position to the shader
		glUniform3fv(glGetUniformLocation(cubeshader.ID, "cameraPos"), 1, glm::value_ptr(camera.Position));
		// set up the flashlight elements
		glUniform3fv(glGetUniformLocation(cubeshader.ID, "lights[2].position"), 1, glm::value_ptr(camera.Position));
		glUniform3fv(glGetUniformLocation(cubeshader.ID, "lights[2].direction"), 1, glm::value_ptr(camera.Front));

		// display the boxes
		elements = DataSource::get_data(Data::Element);
		for (vector<Element>::iterator iter = elements.begin(); iter != elements.end(); ++iter) {
			// select the texture
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, iter->texture);
			glActiveTexture(GL_TEXTURE1);
			// the first element is the terrain: fragile solution
			if (iter->name == DataSource::get_terrain()) {
				glBindTexture(GL_TEXTURE_2D, iter->texture);
			}
			else {
				glBindTexture(GL_TEXTURE_2D, spec_texture);
			}
			compute_model(model, iter->translation, iter->angle, bend, iter->scaleX, iter->scaleY, iter->scaleZ, cubeshader.ID, normalMatrix, false);
			// issuance of the draw call: every uniform in the relevant shaders must have been fed necessary data at this point
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}		
		glUseProgram(0);

		// display light bulbs
		glUseProgram(lightshader.ID);
		glUniformMatrix4fv(glGetUniformLocation(lightshader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(lightshader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		for (vector<Element>::iterator iter = modellights.begin(); iter != modellights.end(); ++iter) {
			compute_model(model, iter->translation, iter->angle, 0.0, iter->scaleX, iter->scaleY, iter->scaleZ, lightshader.ID, normalMatrix, false);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		for (vector<Element>::iterator iter = cubelights.begin(); iter != cubelights.end(); ++iter) {
			compute_model(model, iter->translation, iter->angle, 0.0, iter->scaleX, iter->scaleY, iter->scaleZ, lightshader.ID, normalMatrix, false);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glBindVertexArray(0);
		glUseProgram(0);

		// display models
		glUseProgram(modelshader.ID);
		// pass the matrices and variables to the shaders before the draw call
		glUniformMatrix4fv(glGetUniformLocation(modelshader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(modelshader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		// set up the flash light for models
		glUniform3fv(glGetUniformLocation(modelshader.ID, "lights[1].position"), 1, glm::value_ptr(camera.Position));
		glUniform3fv(glGetUniformLocation(modelshader.ID, "lights[1].direction"), 1, glm::value_ptr(camera.Front));
		glUniform3fv(glGetUniformLocation(modelshader.ID, "cameraPos"), 1, glm::value_ptr(camera.Position));
		// place the model light in the lower right corner of the scene
		glUniform3fv(glGetUniformLocation(modelshader.ID, "lights[0].position"), 1, glm::value_ptr(modellights[0].translation));

		// display 4 spider models: lower right corner scene
		for (vector<Element>::iterator iter = spiders.begin(); iter != spiders.end(); ++iter) {
			compute_model(model, iter->translation, iter->angle, iter->texture, iter->scaleX, iter->scaleY, iter->scaleZ, modelshader.ID, normalMatrix, false);
			spider.Draw(modelshader);
		}
		// upper left corner scene
		// display a dragon
		compute_model(model, glm::vec3(-130.0, 2.0, -205.0), 55.0f, 0, 1.5, 1.5, 1.5, modelshader.ID, normalMatrix, false);
		dragon.Draw(modelshader);
		// chairs
		compute_model(model, glm::vec3(-185.0, 2.0, -210.0), 0.0f, 0, 5, 5, 5, modelshader.ID, normalMatrix, false);
		chairs.Draw(modelshader);
		compute_model(model, glm::vec3(-225.0, 6.1, -200.0), 0.0f, 0, 5, 5, 5, modelshader.ID, normalMatrix, false);
		bed.Draw(modelshader);
		compute_model(model, glm::vec3(-50.0, 2.0, -185.0), 0.0f, 0, 10, 10, 10, modelshader.ID, normalMatrix, false);
		house.Draw(modelshader);
		/// end of scene

		// dispersed
		compute_model(model, glm::vec3(210.0, 9.5, 5.0), 0.0f, 0, 2, 2, 2, modelshader.ID, normalMatrix, false);
		car.Draw(modelshader);
		// display the incredible hulk
		compute_model(model, glm::vec3(150.0, 2.0, 70.0), 45.0f, 0, 4, 4, 4, modelshader.ID, normalMatrix, false);
		hulk.Draw(modelshader);
		compute_model(model, glm::vec3(-210.0, 2.2, -2.0), 0.0f, 0, 4, 4, 4, modelshader.ID, normalMatrix, false);
		ferrari.Draw(modelshader);
		compute_model(model, glm::vec3(-50.0, 2.0, 50.0), 0.0f, 0, 12.0, 6.0, 6.0, modelshader.ID, normalMatrix, false);
		brokenhouse.Draw(modelshader);
		// end of dispersed

		// display the flying plane
		compute_model(model, glm::vec3(60.0, 30.0, 0.0), 75.0f, 0.0, 0.6, 0.6, 0.6, modelshader.ID, normalMatrix, true);
		airplane.Draw(modelshader);

		model = glm::mat4(1.0);
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0, 1.0, 0.0));
		model = glm::translate(model, camera.Position + glm::vec3(0.0, -1.0, 0.0) + camera.Front);
		model = glm::scale(model, glm::vec3(0.025, 0.025, 0.025));
		glUniformMatrix4fv(glGetUniformLocation(modelshader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
		// normal matrix to the fragment shader
		normalMatrix = glm::mat3(glm::transpose(glm::inverse(model)));
		glUniformMatrix3fv(glGetUniformLocation(modelshader.ID, "normalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));
		//compute_model(model, camera.Position + glm::vec3(0.0, -1.0, 0.0) + camera.Front, 0.0f, 0.0, 0.025, 0.025, 0.025, modelshader.ID, normalMatrix, false);
		if(show_gun) gun.Draw(modelshader);

		glUseProgram(0);
		// double-buffering: the function which displays the image in the window
		glfwSwapBuffers(window);
		// a function which calls callback functions of triggered events
		glfwPollEvents();
	}

	// delete buffers
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	// once the loop is terminate, the application can close. first glfw allocated resources must be released
	glfwTerminate();
	return 0;
}

/*function definitions*/
 void compute_model(glm::mat4& model, glm::vec3 translation, float angle, float bent, float scaleX, float scaleY, float scaleZ, unsigned int program, glm::mat3& normalMatrix, bool swap)
{
	 model = glm::mat4(1.0);
	 
	 if (swap) { 
		 model = glm::rotate(model, dir * (rotationSpeed) * (float)(glfwGetTime()) * glm::radians(angle), glm::vec3(bent, 1.0, 0.0));
		 model = glm::translate(model, translation);
	 }
	 else { 
		 model = glm::translate(model, translation);
		 model = glm::rotate(model, dir * (rotationSpeed) * (float)(glfwGetTime()) * glm::radians(angle), glm::vec3(bent, 1.0, 0.0));
	 }

	 model = glm::scale(model, glm::vec3(scaleX, scaleY, scaleZ));
	 glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, glm::value_ptr(model));
	 // normal matrix to the fragment shader
	 normalMatrix = glm::mat3(glm::transpose(glm::inverse(model)));
	 glUniformMatrix3fv(glGetUniformLocation(program, "normalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));
}
// a function to initialise the display window
bool initialise(GLFWwindow* & window)
{
	// initialise glfw
	if (!glfwInit()) {
		std::cout << "GLFW failed to initialise" << std::endl;
		return false;
	}
	// configure glfw
	// make glfw fail if the opengl version installed is below 3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// inform glfw that the application will use opengl core profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// create the window
	window = glfwCreateWindow(WIDTH, HEIGHT, "3D Lighting Scene - The Genesis", NULL, NULL);
	// make sure the window was properly created
	if (window == 0) {
		std::cout << "the creation of the window failed." << std::endl;
		return false;
	}
	// make the window the main context of the current thread
	glfwMakeContextCurrent(window);
	// register callbacks for mouse scrolls and mouse movements
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse. I do not like it.
	// glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// now GLAD can be initialised. GLAD makes it possible to use opengl functions directly in the application
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "GLAD failed to initialise" << std::endl;
		return false;
	}
	return true;
}

// a callback function which is called each time the window is being resized
void resize_window(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// a function to process certain window events
void process_events(GLFWwindow* window)
{
	// close the window when the escape button is pressed
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

// a function used to change the texture of the terrain
void process_terrain(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		static float lastTime = 0.0f;
		static const char* texture = gold_terrain;
		if (glfwGetTime() - lastTime > 3.0f) {
			texture = (texture == gold_terrain) ? grass_terrain : gold_terrain;
			if(texture == gold_terrain) DataSource::create_texture(gold_terrain, GL_RGB);
			else if(texture == grass_terrain) DataSource::create_texture(grass_terrain, GL_RGBA);
			lastTime = glfwGetTime();
		}
	}
}

// a function to activate or deactivate flashlights
void process_flashlight(GLFWwindow* window, unsigned int cubeprogram, unsigned int modelprogram)
{
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		static float lastTime = 0.0f;
		static int status = 1;
		if (glfwGetTime() - lastTime > 3.0f) {
			status = (status == 1) ? 0 : 1;
			glUseProgram(cubeprogram);
			glUniform1i(glGetUniformLocation(cubeprogram, flashlight), status);
			glUseProgram(0);
			glUseProgram(modelprogram);
			glUniform1i(glGetUniformLocation(modelprogram, flashlight), status);
			glUseProgram(0);
			lastTime = glfwGetTime();
		}
	}
}

// a function to process camera movements and update the camera position
void process_camera(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);

	//************Positioning the camera *******************//
	// face the negative z axis by pressing T
	else if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
		static float lastTime = 0;
		show_gun = true;
		// toggle the yaw value per request but every 3 seconds min
		if (glfwGetTime() - lastTime > 3.0) {
			angular = 0.0f;
			camera.Yaw = -90;
			camera.Pitch = 0;
			lastTime = glfwGetTime();
		}
	}
	// when facing the negative z axis, press G to turn back
	else if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
		static float lastTime = 0;
		show_gun = true;
		// toggle the yaw value per request but every 3 seconds min
		if (glfwGetTime() - lastTime > 3.0) {
			camera.Yaw = 90;
			camera.Pitch = 0;
			lastTime = glfwGetTime();
		}
	}
	// when facing the negative z axis, press H to turn right
	else if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
		static float lastTime = 0;
		show_gun = false;
		// toggle the yaw value per request but every 3 seconds min
		if (glfwGetTime() - lastTime > 3.0) {
			camera.Yaw = 0;
			camera.Pitch = 0;
			lastTime = glfwGetTime();
		}
	}
	// when facing the negative z axis, press F to go left
	else if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
		static float lastTime = 0;
		show_gun = false;
		// toggle the yaw value per request but every 3 seconds min
		if (glfwGetTime() - lastTime > 3.0) {
			camera.Yaw = 0;
			camera.Pitch = 180;
			lastTime = glfwGetTime();
		}
	}
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	// reversed since y-coordinates go from bottom to top
	float yoffset = lastY - ypos; 

	lastX = xpos;
	lastY = ypos;

	// camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

/************************end of function definitions*******************************************************************/