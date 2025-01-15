#shader vertex
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;
layout(location = 2) in vec3 aNormal;

out vec2 TexCoord;
out vec3 Colour;
out vec3 Normal;
out vec3 Scale;
flat out int Grid;

uniform vec3 sunDirection;
uniform float sunStrength;
uniform vec3 ambientLight;
uniform float ambientStrength;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;

uniform vec3 colour;
uniform vec3 scale;
uniform int grid;

void main() {
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	TexCoord = aTexCoord;
	
	vec3 ambientColour = ambientLight * ambientStrength;
	
	float shadowStrength = (dot(sunDirection, aNormal) * -sunStrength + 1.0) / 2.0;
	vec3 objectColour = colour * shadowStrength * (1 - ambientStrength);

	Colour = objectColour + ambientColour;
	Normal = aNormal;
	Scale = scale;
	Grid = grid;
}

#shader fragment
#version 330 core

in vec2 TexCoord;
in vec3 Colour;
in vec3 Normal;
in vec3 Scale;
flat in int Grid;

out vec4 FragColor;

uniform sampler2D tex;

float thickEdgeMultiplier = 0.9;
float thickEdgeThickness = 0.05;
float thinEdgeMultiplier = 0.95;
float thinEdgeThickness = 0.025;

void main() {
	vec2 adjustedTexCoord = TexCoord;

	if (Normal.x != 0.0) {
		adjustedTexCoord.x = mod(adjustedTexCoord.x, 1.0 / Scale.z) * Scale.z;
		adjustedTexCoord.y = mod(adjustedTexCoord.y, 1.0 / Scale.y) * Scale.y;
	}

	if (Normal.y != 0.0) {
		adjustedTexCoord.x = mod(adjustedTexCoord.x, 1.0 / Scale.x) * Scale.x;
		adjustedTexCoord.y = mod(adjustedTexCoord.y, 1.0 / Scale.z) * Scale.z;
	}

	if (Normal.z != 0.0) {
		adjustedTexCoord.x = mod(adjustedTexCoord.x, 1.0 / Scale.x) * Scale.x;
		adjustedTexCoord.y = mod(adjustedTexCoord.y, 1.0 / Scale.y) * Scale.y;
	}

	vec3 colour = Colour;

	if (Grid == 1) {
		if (adjustedTexCoord.x < 0.5 + thickEdgeThickness && adjustedTexCoord.x > 0.5 - thickEdgeThickness ||
			adjustedTexCoord.y < 0.5 + thickEdgeThickness && adjustedTexCoord.y > 0.5 - thickEdgeThickness) 
		{
			colour *= thickEdgeMultiplier;
		} else if (mod(adjustedTexCoord.x, 0.25) < thinEdgeThickness || mod(adjustedTexCoord.x, 0.25) > 1.0 - thinEdgeThickness ||
				   mod(adjustedTexCoord.y, 0.25) < thinEdgeThickness || mod(adjustedTexCoord.y, 0.25) > 1.0 - thinEdgeThickness) 
		{
			colour *= thinEdgeMultiplier;
		}
	}

	FragColor = texture(tex, adjustedTexCoord) * vec4(colour, 1.0);
}