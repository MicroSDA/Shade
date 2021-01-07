#version 440

layout (location = 0) in vec2 TextureCoords;

layout(binding = 0) uniform sampler2D TEXTURE;

void main()
{
    gl_FragColor = texture(TEXTURE, TextureCoords);
}