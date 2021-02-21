#pragma once

#include <Shade/Core/Engine/Texture.h>

class AssimpTexture : public se::Texture
{
public:
	AssimpTexture() = default;
	virtual ~AssimpTexture() = default;

	void LoadFromFile(const char* filePath);
private:
};

