#shader vertex
#version 330 core
layout(location = 0) in vec3 aPos;

out vec4 Colour;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;
uniform vec4 colour;

void main() {
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	Colour = colour;
}

#shader fragment
#version 330 core

in vec4 Colour;

out vec4 FragColor;

void main() {
	FragColor = Colour;
}