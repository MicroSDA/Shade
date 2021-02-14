	#version 440
	layout (location = 0) in  vec3  Position;
	layout (location = 0) out vec3  out_Position;
	layout (location = 1) out vec3  out_CameraPosition;
	
	uniform mat4 ModelMatrix;
	uniform mat4 ViewMatrix;
	uniform mat4 ProjectionMatrix;
	uniform vec3 CameraPosition;

	void main()
	{
		gl_Position  = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(Position, 1.0f);
		out_Position = vec3(ModelMatrix * vec4(Position, 1.0f)).xyz;
		out_CameraPosition = CameraPosition;
	}