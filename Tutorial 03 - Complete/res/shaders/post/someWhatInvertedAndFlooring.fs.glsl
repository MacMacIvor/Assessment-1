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

	if (inScreenCoords.x > (float(xScreenRes) / 2.0)) {
		//v.x = inUV.x  * (float(xScreenRes) / 800.0);
		color.r = floor(color.r * 0.6 * 10) / 10;
		color.g = floor(color.g * 0.6 * 10) / 10;
		color.b = floor(color.b * 0.6 * 10) / 10;
		color.rgb = 0.5 - color.rgb;
	}


	


	outColor = vec4(color.rgb, color.a);
}