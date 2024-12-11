#shader vertex
#version 330
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 view;
uniform mat4 projection;

void main() {
	gl_Position = projection * view * vec4(aPos, 1.0f);
	TexCoord = aTexCoord;
}

#shader fragment
#version 330
in vec2 TexCoord;

out vec4 FragColor;

void main() {
	FragColor = vec4(TexCoord, 0.0f, 1.0f);
}