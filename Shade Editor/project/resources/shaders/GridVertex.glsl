	#version 440
	layout (location = 0) in vec3 Position;
	
	uniform mat4 ModelM;
	uniform mat4 ViewM;
	uniform mat4 ProjectionM;

	void main()
	{
		gl_Position = ProjectionM * ViewM * ModelM * vec4(Position, 1.0f);
	}