#version 460 core
out vec4 FragColor;

in vec3 color;
in vec2 texCoord;

uniform sampler2D ourTexture;

void main() {
	vec4 sampledColor = texture(ourTexture, texCoord);

	if (sampledColor.a < 0.1) discard;

	FragColor = sampledColor;
}