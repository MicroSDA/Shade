#version 440
	layout (location = 0) in vec3 Position;
	layout (location = 1) in vec2 TextureCoords;
	layout (location = 2) in vec3 Normals;
	layout (location = 3) in vec3 Tangents;
	
	layout (location = 0) uniform mat4 ModelM;
	layout (location = 1) uniform mat4 ViewM;
	layout (location = 2) uniform mat4 ProjectionM;
	layout (location = 6) uniform vec3 CameraPosition;
		
	layout (location = 0) out vec2 out_TextureCoords;
    layout (location = 1) out vec3 out_Normals;
	layout (location = 2) out vec3 out_ToCameraDirection;
	layout (location = 3) out vec3 out_Position;

	void main()
	{
		gl_Position = ProjectionM * ViewM * ModelM *  vec4(Position, 1.0f);
		out_TextureCoords = TextureCoords;
		out_Normals  = (ModelM * vec4(normalize(Normals), 0.0)).xyz;
		out_Position = (ModelM * vec4(Position, 1.0f)).xyz;
        out_ToCameraDirection  = normalize(CameraPosition - out_Position);
	}