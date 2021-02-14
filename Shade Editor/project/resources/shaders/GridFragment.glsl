	#version 440
	layout (location = 0) in vec3 out_Position;
	layout (location = 1) in vec3 out_CameraPosition;
	
	void main()
	{
		float dist = distance(out_CameraPosition, out_Position);
		vec4 color = vec4(1.0, 1.0, 1.0, 0.1);
		if(dist > 75.0)
			discard;
			
		gl_FragColor = color;
	}