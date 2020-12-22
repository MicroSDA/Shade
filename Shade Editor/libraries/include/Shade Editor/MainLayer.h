#pragma once
#include <Shade/Core/Engine/Layer.h>

class MainLayer :public se::Layer
{
public:
	MainLayer(const std::string& name, se::Scene* scene);
	~MainLayer();
	// Унаследовано через Layer
	virtual void OnCreate() override;
	virtual void OnInit() override;
	virtual void OnUpdate() override;
	virtual void OnRender() override;
	virtual void OnDelete() override;
};

