#pragma once
#include <Shade/Core/Engine/Layer.h>
class GuiLayer :public se::Layer
{
public:
	GuiLayer(const std::string& name, se::Scene* scene);
	~GuiLayer();
	// Inherited via Layer
	virtual void OnCreate() override;
	virtual void OnInit() override;
	virtual void OnUpdate(const se::Timer& deltaTime) override;
	virtual void OnRender() override;
	virtual void OnDelete() override;
};
