#version 440
#include "./project/resources/shaders/VertexUtility.glsl"

	layout (location = 0) in vec3 Position;
	layout (location = 1) in vec2 TextureCoords;
	layout (location = 2) in vec3 Normals;
	layout (location = 3) in vec3 Tangents;
	
	uniform mat4 ModelM;
	uniform mat4 ViewM;
	uniform mat4 ProjectionM;
	uniform vec3 CameraPosition;
		
	layout (location = 0) out vec2 out_TextureCoords;
    layout (location = 1) out vec3 out_Normals;
	layout (location = 2) out vec3 out_ToCameraDirection;
	layout (location = 3) out vec3 out_ModelPosition;

	out mat3 out_TBN;

	void main()
	{
		gl_Position = ProjectionM * ViewM * ModelM *  vec4(Position, 1.0f);
	    out_TBN =  CalculateTBNMatrix(ModelM, Normals, Tangents);
		out_TextureCoords = TextureCoords;
		out_Normals  = (ModelM * vec4(Normals, 0.0)).xyz;
		out_ModelPosition = (ModelM * vec4(Position, 1.0f)).xyz;
        out_ToCameraDirection  = normalize(CameraPosition - out_ModelPosition);
	}