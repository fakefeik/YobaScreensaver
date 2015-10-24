#include "shader.h"
#include "texture.h"
#include "mesh.h"

using namespace glm;

GLFWwindow *window;
Shader *shader;
mat4 projection;
mat4 view;
mat4 model;
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

int main(void) {
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
	glfwSetCursorPosCallback(window, (GLFWcursorposfun)callback_f);
	glfwSwapInterval(1);
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW.\n");
		return -1;
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	projection = perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	view = lookAt(vec3(0, 0, 1.5), vec3(0, 0, -5), vec3(0, 1, 0));
	shader = new Shader();
	shader->bind();
	
	Cube *cube = new Cube();
	cube->LoadTexture("yoba.bmp");

	GLuint uMMatrix = glGetUniformLocation(shader->id(), "uMMatrix");
	GLuint uVMatrix = glGetUniformLocation(shader->id(), "uVMatrix");
	GLuint uPMatrix = glGetUniformLocation(shader->id(), "uPMatrix");

	glUniformMatrix4fv(uVMatrix, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(uPMatrix, 1, GL_FALSE, &projection[0][0]);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	
	float i = 0.0f;
	float j = 0.0f;
	float elapsed = glfwGetTime();
	float delta = 0;
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0 && !shouldClose) {
		delta = glfwGetTime() - elapsed;
		elapsed = glfwGetTime();
		i += delta * 7 / 1.8;
		j += delta * 10 / 1.8;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		model = mat4(1.0f);
		model = translate(model, vec3(0, 0, 1));
		model = rotate(model, i, vec3(0, 1, 0));
		model = rotate(model, j, vec3(0, 0, 1));
		
		glUniformMatrix4fv(uMMatrix, 1, GL_FALSE, &model[0][0]);

        cube->Draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glfwTerminate();

	delete shader;
	delete cube;

	return 0;
}
