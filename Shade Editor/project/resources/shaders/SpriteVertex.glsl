#version 440

layout (location = 0) in vec2 Position;
layout (location = 0) out vec2 out_TextureCoords;

uniform mat4 ModelMatrix;

void main()
{
    gl_Position =  ModelMatrix * vec4(Position.xy, 0.0, 1.0f);
	out_TextureCoords = vec2((Position.x + 1.0) / 2.0, 1 - (Position.y + 1.0) / 2.0);
}