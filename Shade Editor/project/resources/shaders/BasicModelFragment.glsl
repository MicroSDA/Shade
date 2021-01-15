#version 440
#include "./project/resources/shaders/Ligthing.glsl"
#include "./project/resources/shaders/FragmentUtility.glsl" // Isnt supported more then one include, should be enhance

	layout(binding = 0) uniform sampler2D DIFFUSE_TEXTURE;
	layout(binding = 1) uniform sampler2D SPECULAR_TEXTURE;
	layout(binding = 2) uniform sampler2D NORMAL_MAP;
	
	layout (location = 0) in vec2 TextureCoords;
	layout (location = 1) in vec3 Normals;
	layout (location = 2) in vec3 CameraPosition;
	layout (location = 3) in vec3 ModelPosition;

	in mat3 out_TBN;

	void main()
	{
	    vec3 TBNNormal = CalculateTBNNormal(texture(NORMAL_MAP, TextureCoords).rgb, out_TBN);
	
		vec3 ToCameraDirection = normalize(CameraPosition - ModelPosition);

	    vec4 m_TotalColor = ProcessGeneralLight(TBNNormal, generalL, material, ToCameraDirection, texture(DIFFUSE_TEXTURE, TextureCoords).rgba, texture(SPECULAR_TEXTURE, TextureCoords).rgba);
		//vec4 m_TotalColor = ProcessPointLight(TBNNormal, pointL, material, ModelPosition, ToCameraDirection, texture(DIFFUSE_TEXTURE, TextureCoords).rgba, texture(SPECULAR_TEXTURE, TextureCoords).rgba);
		//vec4 m_TotalColor = ProcessSpotLight(TBNNormal, spotL, material, ModelPosition, ToCameraDirection, texture(DIFFUSE_TEXTURE, TextureCoords).rgba, texture(SPECULAR_TEXTURE, TextureCoords).rgba);
		
		gl_FragColor = vec4(pow(m_TotalColor.rgb, vec3(0.70/1)), m_TotalColor.a);
	}