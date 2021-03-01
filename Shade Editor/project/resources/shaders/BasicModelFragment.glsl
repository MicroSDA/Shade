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

	layout (location = 0) out vec4 ColorAttachment1;
	layout (location = 1) out int ColorAttachment2;

	#define MAX_LIGHTNING_SOURCES 100

	uniform BaseLight         generalL;
	uniform PointLight        pointL[MAX_LIGHTNING_SOURCES];
	uniform SpotLight         spotL[MAX_LIGHTNING_SOURCES];
	uniform Material          material;
	uniform int 	          PONT_LIGHTS_COUNT;
	
	in mat3 out_TBN;
	void main()
	{
	    vec3 TBNNormal = CalculateTBNNormal(texture(NORMAL_MAP, TextureCoords).rgb, out_TBN);
		vec3 ToCameraDirection = normalize(CameraPosition - ModelPosition);

		vec4 TotalColor = ProcessGeneralLight(TBNNormal, generalL, material, ToCameraDirection, texture(DIFFUSE_TEXTURE, TextureCoords).rgba, texture(SPECULAR_TEXTURE, TextureCoords).rgba);
		for(int i = 0; i < PONT_LIGHTS_COUNT; i++)
		{
			TotalColor += ProcessPointLight(TBNNormal, pointL[i], material, ModelPosition, ToCameraDirection, texture(DIFFUSE_TEXTURE, TextureCoords).rgba, texture(SPECULAR_TEXTURE, TextureCoords).rgba);
			if(i >= MAX_LIGHTNING_SOURCES - 1)
				break;
		}
		for(int i = 0; i < SPOT_LIGHTS_COUNT; i++)
		{
			TotalColor+= ProcessSpotLight(TBNNormal, spotL[i], material, ModelPosition, ToCameraDirection, texture(DIFFUSE_TEXTURE, TextureCoords).rgba, texture(SPECULAR_TEXTURE, TextureCoords).rgba);
			if(i >= MAX_LIGHTNING_SOURCES - 1)
				break;
		}

		ColorAttachment1 = vec4(pow(TotalColor.rgb, vec3(0.70/1)), 1.0 ); // m_TotalColor.a for imgui alpha shoudl be as 1.0
	}