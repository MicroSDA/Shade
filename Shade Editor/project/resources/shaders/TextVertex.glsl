#version 440

layout (location = 0) in vec2 Position;
layout (location = 1) in vec2 TextureCoords;

layout (location = 0) out vec2 out_TextureCoords;

uniform mat4 ModelMatrix;

void main()
{
    gl_Position =  ModelMatrix * vec4(Position, 0.0, 1.0f);
	out_TextureCoords = TextureCoords;
}