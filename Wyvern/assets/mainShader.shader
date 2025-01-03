#shader vertex
#version 330
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;
layout(location = 2) in vec3 aNormal;

out vec2 TexCoord;
out vec3 Colour;
out vec3 Normal;
out vec3 Scale;

uniform vec3 sunDirection;
uniform float sunStrength;
uniform vec3 ambientLight;
uniform float ambientStrength;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;

uniform vec3 colour;
uniform vec3 scale;

void main() {
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	TexCoord = aTexCoord;
	
	vec3 ambientColour = ambientLight * ambientStrength;
	
	float shadowStrength = (dot(sunDirection, aNormal) * -sunStrength + 1.0) / 2.0;
	vec3 objectColour = colour * shadowStrength * (1 - ambientStrength);

	mat3 normalMatrix = transpose(inverse(mat3(model)));
	vec3 transformedNormal = normalize(normalMatrix * aNormal);

	Colour = objectColour + ambientColour;
	Normal = transformedNormal;
	Scale = scale;
}

#shader fragment
#version 330

in vec2 TexCoord;
in vec3 Colour;
in vec3 Normal;
in vec3 Scale;

out vec4 FragColor;

uniform sampler2D tex;

void main() {
	vec2 adjustedTexCoord = TexCoord;

	if (Normal.x != 0.0 || Normal.z != 0.0) {
		adjustedTexCoord.x = mod(adjustedTexCoord.x, 1.0 / Scale.z) * Scale.z;
		adjustedTexCoord.y = mod(adjustedTexCoord.y, 1.0 / Scale.y) * Scale.y;
	}

	if (Normal.y != 0.0) {
		adjustedTexCoord.x = mod(adjustedTexCoord.x, 1.0 / Scale.x) * Scale.x;
		adjustedTexCoord.y = mod(adjustedTexCoord.y, 1.0 / Scale.z) * Scale.z;
	}

	FragColor = texture(tex, adjustedTexCoord) * vec4(Colour, 1.0);
}