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
	
	if (inScreenCoords.x < (float(xScreenRes) / 2.0)) {
		v.x = inUV.x  * (float(xScreenRes) / 400) - 0.2;
	}
	if (inScreenCoords.x > (float(xScreenRes) / 2.0)) {
		v.x = (inUV.x * (float(xScreenRes) / 400)) - 0.9;
	}

	//Couldn't mirror the top down because I need to modify a z value :(
	//if (inScreenCoords.x < (float(xScreenRes) / 2.0)) {
	//	v.y = inUV.y  * (float(xScreenRes) / 400 - 0.9);
	//}
	//if (inScreenCoords.x > (float(xScreenRes) / 2.0)) {
	//	v.y = (inUV.y * (float(xScreenRes) / 400)) - 0.9;
	//}
	vec4 color = texture(xImage, v);
	outColor = vec4(color.rgb, color.a);
}