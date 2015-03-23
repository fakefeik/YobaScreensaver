#include "shader.h"
#include <string>
#include <fstream>

using namespace std;

Shader::Shader() {
	inited = false;
	init();
}

void Shader::init() {
	if (inited)
		return;
	inited = true;
	shader_vp = glCreateShader(GL_VERTEX_SHADER);
	shader_fp = glCreateShader(GL_FRAGMENT_SHADER);

	const char *vertexText = "#version 330 core\nlayout(location = 0) in vec3 vertexPosition_modelspace;layout(location = 1) in vec2 vertexUV;out vec2 UV;uniform mat4 MVP;void main() {gl_Position = MVP * vec4(vertexPosition_modelspace, 1);UV = vertexUV;}";
	const char *fragmentText = "#version 330 core\nin vec2 UV;out vec4 color;uniform sampler2D tex;void main() {color = texture(tex, UV);}";
	if (vertexText == NULL || fragmentText == NULL) {
		cout << "Either vertex shader or fragment shader file not found." << endl;
		return;
	}

	glShaderSource(shader_vp, 1, &vertexText, 0);
	glCompileShader(shader_vp);

	glShaderSource(shader_fp, 1, &fragmentText, 0);
	glCompileShader(shader_fp);

	shader_id = glCreateProgram();
	glAttachShader(shader_id, shader_vp);
	glAttachShader(shader_id, shader_fp);

	glBindAttribLocation(shader_id, 0, "in_Position");
	glBindAttribLocation(shader_id, 1, "in_Color");

	glLinkProgram(shader_id);
}

Shader::~Shader() {
	glDetachShader(shader_id, shader_fp);
	glDetachShader(shader_id, shader_vp);
	glDeleteShader(shader_fp);
	glDeleteShader(shader_vp);
	glDeleteProgram(shader_id);
}

unsigned int Shader::id() {
	return shader_id;
}

void Shader::bind() {
	glUseProgram(shader_id);
}

void Shader::unbind() {
	glUseProgram(0);
}
