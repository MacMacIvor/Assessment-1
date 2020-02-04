#version 410


layout(location = 0) in vec4 inColor;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec3 inWorldPos;

layout(location = 0) out vec4 outColor;

uniform vec3  a_CameraPos;

uniform vec3  a_AmbientColor;
uniform float a_AmbientPower;
uniform float a_MatShininess;

uniform mat4 a_ModelViewProjection;
uniform mat4 a_Model;
uniform mat4 a_ModelView;

uniform bool a_ambient;
uniform bool a_diffuse;
uniform bool a_specular;
uniform bool a_rimLighting;
uniform bool a_diffuseWarp;
uniform bool a_specularWarp;
//uniform bool a_warm;
//uniform bool a_cold;
//uniform bool a_custom;

// TF2 Shading
const int levels = 5;
const float scaleFactor = 1.0/levels;

const int MAX_LIGHTS = 16;
struct Light{
	vec3  Pos;
	vec3  Color;
	float Attenuation;
};
uniform Light a_Lights[MAX_LIGHTS];
uniform int a_EnabledLights;


vec3 ResolvePointLight(Light light, vec3 norm) {
	// Determine the direction from the position to the light
	vec3 toLight = light.Pos - inWorldPos;

	// Determine the distance to the light (used for attenuation later)
	float distToLight = length(toLight);
	// Normalize our toLight vector
	toLight = normalize(toLight);

	// Determine the direction between the camera and the pixel
	vec3 viewDir = normalize(a_CameraPos - inWorldPos);

	// Calculate the halfway vector between the direction to the light and the direction to the eye
	vec3 halfDir = normalize(toLight + viewDir);



	// Our specular power is the angle between the the normal and the half vector, raised
	// to the power of the light's shininess
	float specPower = pow(max(dot(norm, halfDir), 0.0), a_MatShininess);
	if (a_specular == false) {
		specPower = 0;
	}


	// Finally, we can calculate the actual specular factor
	vec3 specOut = specPower * light.Color;



	// Calculate our diffuse factor, this is essentially the angle between
	// the surface and the light
	float diffuseFactor = max(dot(norm, toLight), 0);
	// Calculate our diffuse output
	vec3  diffuseOut = diffuseFactor * light.Color;
	if (a_diffuse == false) {
		diffuseOut = diffuseOut * 0;
	}


	// We will use a modified form of distance squared attenuation, which will avoid divide
	// by zero errors and allow us to control the light's attenuation via a uniform
	float attenuation = 1.0 / (1.0 + light.Attenuation * pow(distToLight, 2));

	//TF2 Shading
	if (a_diffuseWarp == true && a_diffuse == true) {
		diffuseOut = floor(diffuseOut * levels) * scaleFactor;
	}
	if (a_specularWarp == true && a_specular == true) {
		specOut = floor(specOut * levels) * scaleFactor;
	}
	return attenuation * (diffuseOut + specOut);
}

void main() {
	// Re-normalize our input, so that it is always length 1
	vec3 norm = normalize(inNormal);
	
	// Our ambient is simply the color times the ambient power
	vec3 result = a_AmbientColor * a_AmbientPower;
	if (a_ambient == false) {
		result = result * 0;
	}

	for (int i = 0; (i < a_EnabledLights) && (i < MAX_LIGHTS); i++) {
		result += ResolvePointLight(a_Lights[i], norm);
			
		if (a_rimLighting == true) {
			if (i == 3) { //Only want one light because otherwise it just looks weird (too many lights)
				vec3 yeah = normalize(vec3(a_Lights[i].Pos) * vec3(a_ModelViewProjection));
				vec3 v = normalize(vec3(a_ModelViewProjection) * inWorldPos);
				float rimContrib = 1.0 - max(dot(v, norm), 0.0);
				if (smoothstep(0.9, 1.0, rimContrib) < 0.5) {
					vec3 c = 1 - a_Lights[i].Color;
					result += vec3(smoothstep(0.6, 1.0, rimContrib) * a_Lights[i].Color);
				}
			}
		}
		
	}

	// Multiply the lighting by the object's color
	result = result * inColor.rgb;

	// TODO: gamma correction


	// Write the output
	outColor = vec4(result, inColor.a);
}