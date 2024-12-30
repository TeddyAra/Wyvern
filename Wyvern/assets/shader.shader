#shader vertex
#version 330
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;

out vec2 TexCoord;
flat out int Transform;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;
uniform int transform;

void main() {
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	TexCoord = aTexCoord;
	Transform = transform;
}

#shader fragment
#version 330

in vec2 TexCoord;
flat in int Transform;

out vec4 FragColor;

void main() {
	FragColor = vec4(TexCoord, 0.0f, 1.0f);

	if (Transform > 4) {
		FragColor = vec4(0.0f, 0.0f, 0.5f, 1.0f);
	} else if (Transform > 2) {
		FragColor = vec4(0.0f, 0.5f, 0.0f, 1.0f);
	} else if (Transform > 0) {
		FragColor = vec4(0.5f, 0.0f, 0.0f, 1.0f);
	}
}