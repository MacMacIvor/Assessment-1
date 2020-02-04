#version 440

layout (location = 0) in vec2 inUV;
layout (location = 1) in vec2 inScreenCoords ;

layout (location = 0) out vec4 outColor;

uniform sampler2D xImage;

uniform int xCheckerSize;
uniform vec3 xCheckerColor;
uniform ivec2 xScreenRes;
uniform bool warm;
uniform bool cool;
uniform bool grey;

void main() {
	vec4 color = texture(xImage, inUV);

	if (warm == true) {
		color.rbg = color.rgb * vec3(1.25, 0.3, 0.2);
	}
	if (cool == true) {
		color.rbg = color.rgb * vec3(0.2, 1.25, 0.3);
	}
	if (grey == true) {
		float uni = (color.r + color.b + color.g) / 3.0;
		color.rgb = vec3(uni);
	}

	//if (inScreenCoords.x < (float(xScreenRes) / 2.0)) {
	//	color.b = color.r + color.b;
	//	color.r = 0;
	//}

	//vec3 colorsss = texture2D(xImage, inScreenCoords.st).xyz;
	
	//outColor = vec4(texture3D(warm, colorsss).xyz, 1.0);
	
	//color.rgb = colorsss;

	//void main()
	//{
    //vec3 col = texture2D(framebuf, gl_TexCoord[0].st).xyz;
    //gl_FragColor = vec4(texture3D(lut, col).xyz, 1.0);
	//}



	outColor = vec4(color.rgb, color.a);
}