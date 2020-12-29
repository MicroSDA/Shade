	vec4 Light(vec3 Normals, vec4 Texture)
	{
		return vec4(Texture.rgb * clamp(dot(-vec3(0,0,1), Normals),0.0, 1.0), Texture.a);
	}