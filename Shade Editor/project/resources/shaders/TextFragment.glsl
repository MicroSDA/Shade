#version 440

layout (location = 0) in vec2 TextureCoords;
layout(binding = 0) uniform sampler2D TEXTURE;

const float width = 0.5;
const float edge  = 0.1;

const float borderWidth = 0.5;
const float borderEdge  = 0.4;
const vec2 offset = vec2(0.0, 0.0);

void main()
{
	float distance = 1.0 - texture(TEXTURE, TextureCoords).a;
	float alpha = 1.0 - smoothstep(width, width + edge, distance);
	
	float distance2 = 1.0 - texture(TEXTURE, TextureCoords + offset).a;
	float outlineAlpha = 1.0 - smoothstep(borderWidth, borderWidth + borderEdge, distance2);
	
	float overallAlpha = alpha + (1.0 - alpha) * outlineAlpha;
	
	vec3 overrallColor = mix(vec3(0.2,0.2,0.2), vec3(0.0, 0.5, 0.0) ,alpha/overallAlpha);
    if(overallAlpha <=0.1)
		discard;
    gl_FragColor = vec4(overrallColor, overallAlpha);
}