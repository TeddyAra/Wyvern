#shader vertex
#version 330
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;
uniform float col;

void main() {
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	TexCoord = aTexCoord + vec2(col, col);
}

#shader fragment
#version 330
in vec2 TexCoord;

out vec4 FragColor;

void main() {
	FragColor = vec4(TexCoord, 0.0f, 1.0f);
}