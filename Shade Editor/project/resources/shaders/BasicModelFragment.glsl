#version 440
#include "./project/resources/shaders/Ligthing.glsl"
	layout (location = 0) in vec2 TextureCoords;
	layout (location = 1) in vec3 Normals;
	layout (location = 2) in vec3 ToCameraDirection;

	layout(binding = 0) uniform sampler2D DIFFUSE_TEXTURE;

	void main()
	{
		//gl_FragColor = Light(Normals, texture(DIFFUSE_TEXTURE, TextureCoords).rgba);
		gl_FragColor = ProcessGeneralLight(generalL, material, Normals, texture(DIFFUSE_TEXTURE, TextureCoords).rgba, ToCameraDirection);
	}