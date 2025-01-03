#shader vertex
#version 330 core
layout(location = 0) in vec3 aPos;

out vec3 TexCoord;

uniform mat4 view;
uniform mat4 projection;

void main() {
	vec3 pos = aPos;
	TexCoord = pos;
	
	mat4 viewNoTranslation = mat4(mat3(view));
	gl_Position = projection * viewNoTranslation * vec4(pos, 1.0);
}

#shader fragment
#version 330 core
in vec3 TexCoord;

out vec4 FragColor;

uniform samplerCube skybox;

void main() {
	FragColor = texture(skybox, TexCoord);
}