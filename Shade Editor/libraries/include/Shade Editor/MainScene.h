#pragma once
#include <Shade/Core/Engine/Scene.h>

#include "MainLayer.h"
#include "EditorLayer.h"
#include "ModelPreviewLayer.h"

class MainScene : public se::Scene
{
public:
	MainScene(const std::string& name);
	~MainScene();

	// Унаследовано через Scene
	virtual void OnCreate() override;

	virtual void OnInit() override;

	virtual void OnUpdate(const se::Timer& deltaTime) override;

	virtual void OnRender() override;

	virtual void OnDelete() override;
	virtual void OnEvent(const se::Event& event) override;
private:
	
};

