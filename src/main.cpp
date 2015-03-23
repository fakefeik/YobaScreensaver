#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "shader.h"
#include "texture.h"
#include "mesh.h"
#include <string>
#include <fstream>

using namespace glm;

GLFWwindow *window;
Shader *shader;
glm::mat4 projection;
glm::mat4 view;
bool shouldClose = false;

int prev_x = 0;
int prev_y = 0;

void callback_f(int x, int y) {
	if (prev_x == 0 && prev_y == 0)
	{
		prev_x = x;
		prev_y = y;
	} else
	shouldClose = true;
}

void callback_func(GLFWwindow *window, int width, int height) {
	//projection = glm::perspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);
	std::cout << "New width: " << width << "\nNew height: " << height << std::endl;
}

int main(void) {
	FreeConsole();
	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	int window_width = mode->width;
	int window_height = mode->height;

	window = glfwCreateWindow(window_width, window_height, "YobaScreensaver", glfwGetPrimaryMonitor(), nullptr);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetWindowSizeCallback(window, callback_func);

	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW.\n");
		return -1;
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	view = glm::lookAt(glm::vec3(0, 0, 1.5), glm::vec3(0, 0, -5), glm::vec3(0, 1, 0));
	shader = new Shader();
	
	Cube *cube = new Cube(1, 1, 1);
	cube->LoadTexture("yoba.bmp");
	GLuint MatrixID = glGetUniformLocation(shader->id(), "MVP");
	GLuint TextureID  = glGetUniformLocation(shader->id(), "tex");

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	
	float i = 0.0f;
	float j = 0.0f;
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0 && !shouldClose) {
		glfwSetCursorPosCallback(window, (GLFWcursorposfun)callback_f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shader->bind();

		i += 0.07f * 50;
		j += 0.1f * 50;

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0, 0, 1));
		model = glm::rotate(model, i, glm::vec3(0, 1, 0));
		model = glm::rotate(model, j, glm::vec3(0, 0, 1));
		glm::mat4 ModelViewProjection = projection * view * model;
		
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &ModelViewProjection[0][0]);

        cube->Draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	glfwTerminate();
	return 0;
}
