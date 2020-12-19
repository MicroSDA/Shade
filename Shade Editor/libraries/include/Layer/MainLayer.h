#pragma once
#include <Shade/Shade.h>
#include <Shade/Core/Engine/Layer.h>

class MainLayer :public se::Layer
{
public:
	MainLayer(const std::string& name, se::Scene* scene);
	~MainLayer();
	// Inherited via Layer
	virtual void OnCreate() override;
	virtual void OnInit()   override;
	virtual void OnRender() override;
	virtual void OnUpdate() override;
	virtual void OnDelete() override;

private:
	se::Entity e;
	se::Entity b;
};