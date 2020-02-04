#version 440

layout (location = 0) in vec2 inUV;
layout (location = 1) in vec2 inScreenCoords ;

layout (location = 0) out vec4 outColor;

uniform sampler2D xImage;

uniform int xCheckerSize;
uniform vec3 xCheckerColor;
uniform ivec2 xScreenRes;


void main() {
	//Despite the name, it get's rid of the red
	//Because that change was more noticeable and looked better
	//If you have a problem with that then...
	//I don't know but, too bad I guess?


	vec4 color = texture(xImage, inUV);

	if (inScreenCoords.x < (float(xScreenRes) / 2.0)) {
		color.b = color.r + color.b;
		color.r = 0;
	}

	
	outColor = vec4(color.rgb, color.a);
}