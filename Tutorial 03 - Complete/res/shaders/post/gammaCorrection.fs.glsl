#version 440

layout (location = 0) in vec2 inUV;
layout (location = 1) in vec2 inScreenCoords;

layout (location = 0) out vec4 outColor;

uniform sampler2D xImage;

uniform int xCheckerSize;
uniform vec3 xCheckerColor;
uniform ivec2 xScreenRes;

void main() {
	vec2 v = inUV;
	vec4 color = texture(xImage, v);

	float gamma = 2.2;
    color.rgb = pow(color.rgb, vec3(1.0/gamma));


	


	outColor = vec4(color.rgb, color.a);
}