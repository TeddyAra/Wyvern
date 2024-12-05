#include "Renderer.h"

const unsigned int indices[] = {
	0, 2, 3,
	0, 3, 1
};

const float vertices[] = {
	-0.25f, -0.25f, 0.0f, 0.0f,
	 0.25f, -0.25f, 1.0f, 0.0f,
	-0.25f,  0.25f, 0.0f, 1.0f,
	 0.25f,  0.25f, 1.0f, 1.0f
};

Renderer::Renderer(GLFWwindow* window)
	: window(window), VAO(0), VBO(0), EBO(0), shaderProgram(0)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_TEXTURE_2D);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 16 * sizeof(float), vertices, GL_STATIC_DRAW);

	//index, size, type, normalized, stride, pointer
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	const char* vertexShaderSource = R"(
		#version 330 core
		layout(location = 0) in vec3 aPos;
		layout(location = 1) in vec2 aTexCoord;

		out vec2 TexCoord;

		void main() {
			gl_Position = aPos;
			TexCoord = aTexCoord;
		}
	)";

	const char* fragmentShaderSource = R"(
		#version 330 core
		in vec2 TexCoord;
		
		out vec4 FragColor;

		void main() {
			FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f); //vec4(TexCoord, 0.0f, 1.0f);
		}
	)";

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glUseProgram(shaderProgram);
}

Renderer::~Renderer() {

}

void Renderer::render() {
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}