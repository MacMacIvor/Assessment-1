#version 410
layout (location = 0) in vec2 inPosition;
layout (location = 1) in vec2 inUV;

layout (location = 0) out vec2 outUV;
layout (location = 1) out vec2 outScreenCoords;

uniform ivec2 xScreenRes;

void main() {
	vec3 v = vec3(inPosition, 0);
	vec2 coord = ((inPosition + vec2(1, 1)) / 2.0f) * xScreenRes;
	v.x = v.x;

	outScreenCoords = ((inPosition + vec2(1, 1)) / 2.0f) * xScreenRes;
	gl_Position = vec4(v, 1);
	outUV = inUV;
}