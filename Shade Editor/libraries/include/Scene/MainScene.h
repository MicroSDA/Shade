#pragma once
#include <Shade/Shade.h>
#include <Layer/MainLayer.h>

class MainScene : public se::Scene
{
public:
	MainScene(const std::string& name) :Scene(name) {}
	~MainScene() {}
	// Inherited via Scene
	virtual void OnCreate() override;

	virtual void OnInit() override;

	virtual se::SceneState OnUpdate() override;

	virtual void OnRender() override;

	virtual void OnDelete() override;

private:
	
};
