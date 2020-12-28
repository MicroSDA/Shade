	vec4 Light(vec3 Normals)
	{
		return vec4(0.5, 0.5, 0.5, 1.0) * clamp(dot(-vec3(0,0,1), Normals),0.0, 1.0);
	}