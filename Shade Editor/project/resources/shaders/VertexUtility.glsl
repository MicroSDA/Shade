mat3 CalculateTBNMatrix(mat4 ModelMatrix, vec3 Normals, vec3 Tangents)
{
	vec3 T = normalize(vec3(ModelMatrix * vec4(Tangents, 0.0)));
	vec3 N = normalize(vec3(ModelMatrix * vec4(Normals, 0.0)));
	T = normalize(T - dot(T, N) * N);
	vec3 B = normalize(cross(T, N));

	if (dot(cross(N, T), B) > 0.0)
             T = T * -1.0;

	return mat3(T, B, N);
}