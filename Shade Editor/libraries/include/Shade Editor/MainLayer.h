#pragma once
#include <Shade/Core/Engine/Layer.h>

class MainLayer :public se::Layer
{
public:
	MainLayer(const std::string& name, se::Scene* scene);
	virtual ~MainLayer();
	// Унаследовано через Layer
	virtual void OnCreate() override;
	virtual void OnInit() override;
	virtual void OnRenderBegin() override;
	virtual void OnRender() override;
	virtual void OnRenderEnd() override;
	virtual void OnUpdate(const se::Timer& deltaTime) override;
	virtual void OnDelete() override;
private:
};

